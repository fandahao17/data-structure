
def list_sort(src, dest):
    dest_index = 0
    while src: #not empty
        min_index = 0
        for i in range(len(src)):
            if src[i] < src[min_index]:
                min_index = i
        dest.append(src[min_index])
        dest_index += 1
        src.remove(src[min_index]) 

def list_append(first, second, dest):
    for i in range(len(first)):
        dest.append(first[i])
    for j in range(len(second)):
        if second[j] in dest:
            continue
        dest.append(second[j])

def unordered_merge(l1, l2, l3):
    """extend l1 with l2 first, then sort the resulting list.
    >>> l1 = [1, 3, 5]
    >>> l2 = [1, 0, -3]
    >>> answer = []
    >>> unordered_merge(l1, l2, answer)
    [-3, 0, 1, 3, 5]
    >>> l2, answer = [], []
    >>> unordered_merge(l1, l2, answer)
    [1, 3, 5]
    """
    merge_helper = []
    list_append(l1, l2, merge_helper)
    list_sort(merge_helper, l3)
    print(l3)
