import tsplib95
from pprint import pprint
# from anneal import SimAnneal

def input_reader_and_maker():
	data = "d1291"
	problem = tsplib95.load("tsplib/"+data+".tsp")
	data = "Data_For_TSP/"+data
	# print(list(problem.get_nodes()))
	# dct= problem.as_name_dict()
	open(data+"_vertical.txt","w")
	nodes = len(list(problem.get_nodes()))
	with open(data+"_vertical.txt","a+") as fl:
		
		fl.write(str(nodes)+"\n")

		for i in range(1,nodes+1):
			for j in range(i,nodes+1):
				if(i == j):
					continue

				wgt = tsplib95.distances.euclidean(problem.node_coords[i],problem.node_coords[j])
				fl.write(str(i-1)+" "+str(j-1)+" "+str(wgt)+"\n")
				fl.write(str(j-1)+" "+str(i-1)+" "+str(wgt)+"\n")
	
	# dct= problem.as_name_dict()
	# coords = dct["node_coords"]
	# open(data+"_coord.txt","w")
	# with open(data+"_coord.txt","a+") as fl:
	# 	for idx in coords:
	# 		fl.write(str(idx) +" ")
	# 		sing_coord = coords[idx]
	# 		fl.write(str(sing_coord[0]) +" "+str(sing_coord[1])+"\n")



def main():
	input_reader_and_maker()
	

if __name__ == '__main__':
	main()