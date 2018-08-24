import probability
import matplotlib.pyplot as plt
import random
from collections import Counter

smooth = 10.0
i_s = []
for j in range(1000):
    i = random.randint(-50, 50)
    i_s.append(i/smooth)

i_s.sort()
pdf_s = []
cdf_s = []
hst_s = []
for i in i_s:
    pdf_s.append(probability.normal_pdf(i))
    cdf_s.append(probability.normal_cdf(i))
    hst_s.append(probability.binomial(0.75, 100))

plt.plot(i_s, pdf_s)
plt.show()

plt.plot(i_s, cdf_s)
plt.show()

gmrHist = Counter(hst_s)
plt.bar(gmrHist.keys(), gmrHist.values())
plt.show()

smooth = 2.0
i_s = []
for j in range(1000):
    i = random.randint(-50, 50)
    i_s.append(i/smooth)

i_s.sort()
pdf_s = []
cdf_s = []
hst_s = []
for i in i_s:
    pdf_s.append(probability.normal_pdf(i))
    cdf_s.append(probability.normal_cdf(i))
    hst_s.append(probability.binomial(0.75, 100))

plt.plot(i_s, pdf_s)
plt.show()

plt.plot(i_s, cdf_s)
plt.show()

gmrHist = Counter(hst_s)
plt.bar(gmrHist.keys(), gmrHist.values())
plt.show()
