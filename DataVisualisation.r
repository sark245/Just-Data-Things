mydata = read.csv("Big Mart Dataset - Sheet1.csv")
mydata

##########################################################################

#ScatterPlot
#used to see relationship between two continuous variables

#In the dataset, if we want to visualise the iterms as per their 
#cost data, then we can use scatterplot using two continuous variable
#Item_Visibility and Item_MRP

library(ggplot2)
 #Example 1
ggplot(mydata, aes(Item_Visibility, Item_MRP)) +
  geom_point() + scale_x_continuous("Item_Visibility", breaks = seq(0,0.35,0.05))+
  scale_y_continuous("Item_MRP", breaks = seq(0, 270, by = 30))+theme_bw()

#aes(x,y)
#scale_x_continuous("Tag", breaks)
#breaks: to control the breaks in the guide
#     NULL: hide all breaks
#     waiver(): the default break computation
#     a char or numeric vector to specify the breaks to display


#Example 2
#Addition of a categorical variable(Item_Type)
ggplot(mydata, aes(Item_Visibility, Item_MRP)) + 
  geom_point(aes(color = Item_Type)) +
  scale_x_continuous("Item Visibility", breaks = seq(0, 0.35, 0.05)) +
  scale_y_continuous("Item_MRP", breaks = seq(0,270,by = 30)) +
  theme_bw() + labs(title = "ScatterPlot")
  
#Example 3
#Separate Category wise Chart

ggplot(mydata, aes(Item_Visibility, Item_MRP)) + 
  geom_point(aes(color = Item_Type)) + 
  scale_x_continuous("Item Visibility", breaks = seq(0, 0.35, 0.05)) +
  scale_y_continuous("Item MRP", breaks = seq(0,270, by = 30)) +
  theme_bw() + labs(title = "ScatterPlot") + facet_wrap(~Item_Type)
  
##########################################################################

# Histogram
#Used to plot continuous variable. Breaks data into bins and shows their 
#frequencies. 

ggplot(mydata, aes(Item_MRP)) + geom_histogram(binwidth = 2) + 
  scale_x_continuous("Item MRP", breaks = seq(0,270,by = 30)) +
  scale_y_continuous("Count", breaks = seq(0,200, by = 20)) + 
  labs(title = "Histogram")

##########################################################################

#Bar and Stack Bar Chart
#Bar charts are used when you want to plot a categorical variable or a 
#combination of continuous and categorical variable

#Example: Number of Marts established in a particular year

#For a single continuous variable
ggplot(mydata, aes(Outlet_Establishment_Year)) + 
  geom_bar(fill = "red") + theme_bw() + 
  scale_x_continuous("Establishment Year", breaks = seq(1985, 2010)) +
  scale_y_continuous("Count", breaks = seq(0, 1500, 150))+
  coord_flip() + labs(title = "Bar Chart") + theme_gray()

#Without "coord_flip()"
ggplot(mydata, aes(Outlet_Establishment_Year)) + 
  geom_bar(fill = "red") + theme_bw() + 
  scale_x_continuous("Establishment Year", breaks = seq(1985, 2010)) +
  scale_y_continuous("Count", breaks = seq(0, 1500, 150))+
   labs(title = "Bar Chart") + theme_gray()

#Example 3
ggplot(mydata, aes(Item_Type, Item_Weight)) + 
  geom_bar(stat = "identity", fill = "darkblue") +
  scale_x_discrete("Outlet Type") + 
  scale_y_continuous("Item Weight", breaks = seq(0, 15000, by = 500)) +
  theme(axis.text.x = element_text(angle = 90, vjust = 0.5)) + 
  labs("Bar Chart")


#Example 4
#Stacked Bar Chart
#Used to visualise a combination of categorical variable

ggplot(mydata, aes(Outlet_Location_Type, fill = Outlet_Type)) + geom_bar() +
  labs(title = "Stacked Bar Chart", x = "Outlet Location Type", 
       y = "Count of Outlets")


##########################################################################

#Box Plot
#Used to plot a combination of categorical and continuous variables.
#This plot is useful for visualizing the spread of the data and detect 
#outliers. It shows five statistically significant numbers- the minimum,
#the 25th percentile, the median, the 75th percentile and the maximum.

ggplot(mydata, aes(Outlet_Identifier, Item_Outlet_Sales)) + 
  geom_boxplot(fill = "red") + 
  scale_y_continuous("Item Outlet Sales", breaks = seq(0,15000, by=500))+
  labs(title="Box Plot", x = "Outlet Identifier")


##########################################################################

#Area Chart
#Used to show continuity across a variable or data set.

ggplot(mydata, aes(Item_Outlet_Sales)) + geom_area(stat = "bin", bins=30, fill = "red")+
  scale_x_continuous(breaks = seq(0,11000, 1000)) +
  labs(title = "Area Chart", x = "Item Outlet Sales", y = "Count")
                                              
#In geom_area(position, stat)
#position: Position Adjustments to points
#stat: Statistical Transformation to use on the data for this layer
#bins: Equal parts in which the data set is divided into, basically 
#       class intervals.



##########################################################################

#HeatMaps

#Uses Intensity of colors to display relationship between multiple variables
#Basically presents 3 dimensions to analyse


#Example: We want to know cost of each item on every outlet,
#         use: Item MRP, Outlet Identifier, Item Type

ggplot(mydata, aes(Outlet_Identifier, Item_Type)) +
  geom_raster(aes(fill = Item_MRP)) +
  labs(title="HeatMap", x = "Outlet Identifier", y = "Item Type") +
  scale_fill_continuous(name = "Item MRP")


##########################################################################









  
  
  