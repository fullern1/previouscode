import numpy as np
import thinkstats2
import thinkplot


def ReadFemPreg(dct_file='2002FemPreg.dct',
                dat_file='2002FemPreg.dat.gz'):
    """Reads the NSFG pregnancy data.

    dct_file: string file name
    dat_file: string file name

    returns: DataFrame
    """
    dct = thinkstats2.ReadStataDct(dct_file)
    df = dct.ReadFixedWidth(dat_file, compression='gzip')
    CleanFemPreg(df)
    return df


def CleanFemPreg(df):
    """Recodes variables from the pregnancy frame.

    df: DataFrame
    """
    # mother's age is encoded in centiyears; convert to years
    df.agepreg /= 100.0

    # birthwgt_lb contains at least one bogus value (51 lbs)
    # replace with NaN
    df.loc[df.birthwgt_lb > 20, 'birthwgt_lb'] = np.nan

    # replace 'not ascertained', 'refused', 'don't know' with NaN
    na_vals = [97, 98, 99]
    df.birthwgt_lb.replace(na_vals, np.nan, inplace=True)
    df.birthwgt_oz.replace(na_vals, np.nan, inplace=True)
    df.hpagelb.replace(na_vals, np.nan, inplace=True)

    df.babysex.replace([7, 9], np.nan, inplace=True)
    df.nbrnaliv.replace([9], np.nan, inplace=True)

    # birthweight is stored in two columns, lbs and oz.
    # convert to a single column in lb
    # NOTE: creating a new column requires dictionary syntax,
    # not attribute assignment (like df.totalwgt_lb)
    df['totalwgt_lb'] = df.birthwgt_lb + df.birthwgt_oz / 16.0

    # due to a bug in ReadStataDct, the last variable gets clipped;
    # so for now set it to NaN
    df.cmintvw = np.nan


def MakeFrames():
    """Reads pregnancy data and partitions first babies and others.

    returns: DataFrames (all live births, first babies, others)
    """
    preg = ReadFemPreg()

    greq = preg[preg.agepreg >= 30]
    less = preg[preg.agepreg < 30]

    assert len(greq) == 2635
    assert len(less) == 10606

    return greq, less


def MakeHists(greq, less):
    """Plot Hists for live births

    live: DataFrame
    others: DataFrame
    """
    hist = thinkstats2.Hist(greq.prglngth, label='prglngth')
    thinkplot.Hist(hist)
    # thinkplot.Save(root='greq_prglngth_hist',
    #                xlabel='weeks',
    #                ylabel='frequency',
    #                axis=[-1, 53, 0, 1000])
    thinkplot.Show()

    hist = thinkstats2.Hist(less.prglngth, label='prglngth')
    thinkplot.Hist(hist)
    # thinkplot.Save(root='less_prglngth_hist',
    #                xlabel='weeks',
    #                ylabel='frequency',
    #                axis=[-1, 53, 0, 5000])
    thinkplot.Show()


def MakePmfs(greq, less):
    width = 0.45
    axis = [0, 50, 0, 0.6]

    greqpmf = thinkstats2.Pmf(greq.prglngth, label='greater/equal to 30')
    lesspmf = thinkstats2.Pmf(less.prglngth, label='less than 30')
    thinkplot.Hist(lesspmf, align='left', width=width)
    thinkplot.Hist(greqpmf, align='right', width=width)
    thinkplot.Config(axis=axis)
    thinkplot.Show()


def MakeStep(greq, less):
    axis = [0, 50, 0, 0.6]

    greqpmf = thinkstats2.Pmf(greq.prglngth, label='greater/equal to 30')
    lesspmf = thinkstats2.Pmf(less.prglngth, label='less than 30')
    thinkplot.Pmfs([greqpmf, lesspmf])
    thinkplot.Config(xlabel='Pregnancy length(weeks)', axis=axis)
    thinkplot.Show()


def Summarize(greq, less):
    """Print various summary statistics."""

    gMean = greq.prglngth.mean()
    gVar = greq.prglngth.var()

    print '>= 30 mean:', gMean
    print'>= 30 variance:', gVar

    lMean = less.prglngth.mean()
    lVar = less.prglngth.var()

    print '< 30 mean:', lMean
    print '< 30 variance:', lVar

    print 'Difference between means:', (abs(gMean-lMean))

    d = thinkstats2.CohenEffectSize(greq.prglngth, less.prglngth)
    print 'Cohen d:', d


greq, less = MakeFrames()
Summarize(greq, less)
MakeHists(greq, less)
MakePmfs(greq, less)
MakeStep(greq, less)