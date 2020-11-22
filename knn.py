from operator import ne, neg
import pandas as pd
import numpy as np
import math
import operator

data = pd.read_csv('iris.csv')

print(data.head(5))

#This is used to calculate the distance between datapoints
def euclideanDistance(data1, data2, length):
    distance = 0
    for x in range(length):
        distance += np.square(data1[x] - data2[x])
    return np.sqrt(distance)

def knn(trainingSet, testInstance, k):
    distances = {}
    length = testInstance.shape[1]

    for x in range(len(trainingSet)):
        dist = euclideanDistance(testInstance, trainingSet.iloc[x], length)
        distances[x] = dist[0];         #As dist is a dataframe


    sorted_d = sorted(distances.items(), key = operator.itemgetter(1))

    neighbours = []

    for x in range(k):
        neighbours.append(sorted_d[x][0])
    
    classVotes = {}
    for x in range(len(neighbours)):
        response = trainingSet.iloc[neighbours[x]][-1]  

        if response in classVotes:
            classVotes[response] += 1
        else :
            classVotes[response] = 1
        
    sortedVotes = sorted(classVotes.items(), key = operator.itemgetter(1), reverse = True)

    return (sortedVotes[0][0], neighbours)


testSet = [[7.2, 3.6, 5.1, 2.5]]
test = pd.DataFrame(testSet)


#print(euclideanDistance(test, data.iloc[0], 4))


print('\n\nWith 1 Nearest Neighbour \n\n')

k = 1
result, neigh = knn(data, test, k)

print('\nPredicted Class of the datapoint = ', result)

print('\nNearest Neighbours of the datapoints = ', neigh)

print('\n\nWith 5 Nearest Neighbours\n\n')

k = 5
result, neigh = knn(data, test, k)

print('\nPredicted class of the datapoint = ', result)

print('\nNearest Neighbours of the datapoints = ', neigh)
