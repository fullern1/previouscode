import pandas as pd
import numpy as np
import thinkstats2
import thinkplot


def ReadData():
    df = pd.read_stata('ESS7e02_1.dta', columns=['gndr', 'alcwknd'], convert_categoricals=False)
    CleanData(df)
    return df


def CleanData(df):
    naVals = [6666, 7777, 8888, 9999]
    df.alcwknd.replace(naVals, np.nan, inplace=True)
    return df


def MakeFrames():
    df = ReadData()

    male = df[df.gndr == 1].dropna()
    female = df[df.gndr == 2].dropna()

    return male, female


def MakeHists(male, female):
    """Plot Hists for live births

    live: DataFrame
    others: DataFrame
    """
    thinkplot.PrePlot(rows=1, cols=2)
    hist = thinkstats2.Hist(male.alcwknd)
    thinkplot.SubPlot(1)
    thinkplot.Config(axis=[0, 800, 0, 600], ylabel='Number of people', xlabel='Alcohol consumed (grams)',
                     title='Weekend Alcohol Consumption for Men')
    thinkplot.Hist(hist, alpha=1)

    hist = thinkstats2.Hist(female.alcwknd)
    thinkplot.SubPlot(2)
    thinkplot.Config(axis=[0, 800, 0, 1200], ylabel='Number of people', xlabel='Alcohol consumed (grams)',
                     title='Weekend Alcohol Consumption for Women')
    thinkplot.Hist(hist, alpha=1)
    thinkplot.Show()


def MakePmfs(male, female):
    width = 0.45
    axis = [0, 800, 0, 0.1]

    malepmf = thinkstats2.Pmf(male.alcwknd, label='Male')
    femalepmf = thinkstats2.Pmf(female.alcwknd, label='Female')
    thinkplot.Hist(malepmf, align='left', width=width)
    thinkplot.Hist(femalepmf, align='right', width=width)
    thinkplot.Config(xlabel='Alcohol Consumption (grams)', ylabel='PMF', axis=axis, title='Weekend Alcohol Consumption')
    thinkplot.Show()


def MakeStep(male, female):
    axis = [0, 800, 0, 0.1]

    malepmf = thinkstats2.Pmf(male.alcwknd, label='Male')
    femalepmf = thinkstats2.Pmf(female.alcwknd, label='Female')
    thinkplot.Pmfs([malepmf, femalepmf])
    thinkplot.Config(xlabel='Alcohol Consumption (grams)', ylabel='PMF', axis=axis, title='Weekend Alcohol Consumption')
    thinkplot.Show()


def MakeCdfs(male, female):
    malecdf = thinkstats2.Cdf(male.alcwknd, label='Male')
    femalecdf = thinkstats2.Cdf(female.alcwknd, label='Female')
    thinkplot.PrePlot(2)
    thinkplot.Cdfs([malecdf, femalecdf])
    thinkplot.Config(xlabel='Alcohol Consumed (grams)', ylabel='CDF', title='Weekend Alcohol Consumption')
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


male, female = MakeFrames()
alcwknd = male.alcwknd, female.alcwknd
MakeHists(male, female)
MakePmfs(male, female)
MakeStep(male, female)
MakeCdfs(male, female)
ht = DiffMeansPermute(alcwknd)
pvalue = ht.PValue()
ht.PlotCdf()
thinkplot.Config(xlabel='Difference in Means', ylabel='CDF', title='Weekend Alcohol Consumption')
thinkplot.Show()
print 'Weekend Alcohol Consumption:\nMen:\nMean:', male.alcwknd.mean(), '\nVariance:', male.alcwknd.var()
print '\nWomen:\nMean:', female.alcwknd.mean(), '\nVariance:', female.alcwknd.var()
print '\nDifference in means:', abs(male.alcwknd.mean()-female.alcwknd.mean())
print '\nCohen d:', thinkstats2.CohenEffectSize(male.alcwknd, female.alcwknd)
print '\np-value:', pvalue
