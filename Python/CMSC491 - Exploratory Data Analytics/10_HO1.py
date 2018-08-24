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


def SplitFrames(df):
    df = df.dropna(subset=['agepreg', 'totalwgt_lb'])
    age = df.agepreg
    wgt = df.totalwgt_lb
    return age, wgt


def PlotScatter(age, wgt, xmin, xmax, ymin, ymax):
    thinkplot.Scatter(age, wgt, alpha=1.0)
    thinkplot.Config(xlabel='Age (Years)', ylabel='Birth Weight (lbs)', xlim=[xmin, xmax], ylim=[ymin, ymax], legend=False)
    thinkplot.Show()


greq, less = MakeFrames()
greqage, greqwgt = SplitFrames(greq)
lessage, lesswgt = SplitFrames(less)
PlotScatter(greqage, greqwgt, 30, 50, 0, 14)
PlotScatter(lessage, lesswgt, 5, 30, 0, 14)
print "Greq 30 Pearson's corr:", thinkstats2.Corr(greqage, greqwgt)
print "Greq 30 Spearman corr:", thinkstats2.SpearmanCorr(greqage, greqwgt)
print "Less 30 Pearson's corr:", thinkstats2.Corr(lessage, lesswgt)
print "Less 30 Spearman corr:", thinkstats2.SpearmanCorr(lessage, lesswgt)
