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
    babies = ReadFemPreg()

    boys = babies[babies.babysex == 1]
    girls = babies[babies.babysex == 2]

    return boys, girls


def MakeCdfs(male, female):
    malecdf = thinkstats2.Cdf(male.totalwgt_lb, label='Male')
    femalecdf = thinkstats2.Cdf(female.totalwgt_lb, label='Female')
    thinkplot.PrePlot(2)
    thinkplot.Cdfs([malecdf, femalecdf])
    thinkplot.Config(xlabel='Baby Weight (Lbs)', ylabel='CDF', title='Baby Weights')
    thinkplot.Show()


def UnimplementedMethodException():
    print 'not implemented'


class HypothesisTest(object):
    def __init__(self, data):
        self.data = data
        self.MakeModel()
        self.actual = self.TestStatistic(data)

    def PValue(self, iters=1000):
        self.test_stats = [self.TestStatistic(self.RunModel()) for _ in range(iters)]
        count = sum(1 for x in self.test_stats if x >= self.actual)
        return count / iters

    def TestStatistic(self, data):
        raise UnimplementedMethodException()

    def MakeModel(self):
        pass

    def RunModel(self):
        raise UnimplementedMethodException()


class DiffMeansPermute(thinkstats2.HypothesisTest):
    def TestStatistic(self, data):
        group1, group2 = data
        test_stat = abs(group1.mean() - group2.mean())
        return test_stat

    def MakeModel(self):
        group1, group2 = self.data
        self.n, self.m = len(group1), len(group2)
        self.pool = np.hstack((group1, group2))

    def RunModel(self):
        np.random.shuffle(self.pool)
        data = self.pool[:self.n], self.pool[self.n:]
        return data


boys, girls = MakeFrames()
MakeCdfs(boys, girls)
babyweights = boys.totalwgt_lb, girls.totalwgt_lb
ht = DiffMeansPermute(babyweights)
pvalue = ht.PValue()
# plot not needed
# ht.PlotCdf()
# thinkplot.Config(xlabel='Difference in means', ylabel='CDF')
# thinkplot.Show()
print 'p-value:', pvalue
print 'boys mean weight:', boys.totalwgt_lb.mean()
print 'girls mean weight:', girls.totalwgt_lb.mean()
print 'diff in means:', abs(boys.totalwgt_lb.mean()-girls.totalwgt_lb.mean())
