def partition(best_distances, best_neighbors, low, high):
	i = (low-1)    # index of smaller element 
	pivot = best_distances[high]   # pivot 
	pivot2 = best_neighbors[high]
	for j in range(low, high):
  
		# If current element is smaller than or
		# equal to pivot
		if best_distances[j] <= pivot:
  
			# increment index of smaller element 
			i = i+1
			best_distances[i], best_distances[j] = best_distances[j], best_distances[i]
			best_neighbors[i], best_neighbors[j] = best_neighbors[j], best_neighbors[i]
  
	best_distances[i+1], best_distances[high] = best_distances[high], best_distances[i+1]
	best_neighbors[i+1], best_neighbors[high] = best_neighbors[high], best_neighbors[i+1]
	return (i+1)


def quickSort(best_distances, best_neighbors, low, high):
	if len(best_distances) == 1:
		return best_distances
	if low < high:
  
		# pi is partitioning index, best_distances[p] and best_neighbors[p] are now
		# at right place 
		pi = partition(best_distances, best_neighbors, low, high)
  
		# Separately sort elements before 
		# partition and after partition 

		quickSort(best_distances, best_neighbors, low, pi-1)
		quickSort(best_distances, best_neighbors, pi+1, high)
