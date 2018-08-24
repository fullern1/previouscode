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


def MakePdfs(greq, less):
    greqpdf = thinkstats2.EstimatedPdf(greq.totalwgt_lb.dropna())
    lesspdf = thinkstats2.EstimatedPdf(less.totalwgt_lb.dropna())
    thinkplot.PrePlot(rows=1, cols=2)
    thinkplot.SubPlot(1)
    thinkplot.Pdf(greqpdf, label='greater/equal to 30')
    thinkplot.Config(xlabel='Birth weight (lbs)', ylabel='PDF')
    thinkplot.SubPlot(2)
    thinkplot.Pdf(lesspdf, label='less than 30')
    thinkplot.Config(xlabel='Birth weight (lbs)', ylabel='PDF')
    thinkplot.Show()


greq, less = MakeFrames()
MakePdfs(greq, less)
print "greater/equal to 30 skew:", thinkstats2.Skewness(greq.totalwgt_lb.dropna())
print "less than 30 skew:", thinkstats2.Skewness(less.totalwgt_lb.dropna())
print "greater/equal to 30 mean:", thinkstats2.Mean(greq.totalwgt_lb.dropna())
print "greater/equal to 30 median:", thinkstats2.Median(greq.totalwgt_lb.dropna())
print "less than 30 mean:", thinkstats2.Mean(less.totalwgt_lb.dropna())
print "less than 30 median:", thinkstats2.Median(less.totalwgt_lb.dropna())
