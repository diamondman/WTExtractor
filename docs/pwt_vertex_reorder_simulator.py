def swap(arr, i, j):                       
    arr[i], arr[j] = arr[j], arr[i]

def checkflip(arr, selector, bitnum, vcount):
    offset = 0                                         
    if ( bitnum <= 0 ):        
        number_from_bit = 0
    else:                                                    
        number_from_bit = 1 << (bitnum - 1)                  
    i = 0                         
    while True:                            
        if selector != i and\              
        arr[offset] - arr[selector] < number_from_bit:
            return False                   
        i += 1                             
        offset += 1                        
        if i >= vcount:                    
            break 
    return True

a = [14, 12, 17, 16, 15, 14, 4, 16, 14, 15]
i = 0                                                  
vcount = len(a)                
ncount = 0         
vndiff = vcount - ncount                                     
while True:                                                  
    if checkflip(a, i, 0, vcount):
        print("SWAP", i, vcount-ncount-1)  
        swap(a, i, vcount-ncount-1)        
        ncount += 1                        
        i -= 1                             
    i += 1                                 
    vndiff = vcount - ncount               
    if i >= vndiff:                        
        break 
