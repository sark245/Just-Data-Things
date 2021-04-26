import numpy as np

class DecisionNode:
    def __init__(self, index, value, left, right):
        self.index, self.value = index, value
        self.left, self.right = left, right

class Leaf:
    def __init__(self, y):
        self.counts = dict(zip(*np.unique(y, return_counts=True)))
        self.prediction = max(self.counts.keys(), key = lambda x : self.counts[x])

def gini_impurity(y):
    m = y.shape[0]
    cnts = dict(zip(*np.unique(y, return_counts=True)))
    impurity = 1 - sum((cnt/m) ** 2 for cnt in cnts.values())
    return impurity

def entropy(y):
    m = y.shape[0]
    cnts = dict(zip(*np.unique(y, return_counts=True)))
    disorder = - sum((cnt/m) * log(cnt/m) for cnt in cnts.values())
    return disorder