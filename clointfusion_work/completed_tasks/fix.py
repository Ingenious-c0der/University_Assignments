def print_with_magic_color(strMsg:str="",magic:bool=False)->None:
    """
    Function used for printing strings in color
    Args : Message (str): string which needs to be printed in color
           magic : (bool) :If each letter/character in the string is to be printed with different color
    Returns : None

    """
    from colored import fg, attr
    import random 
    
    accepted_colors_ints = [i for i in range(0,255) if i not in [8,*range(15,28),*range(51,68),77,*range(87,99),114,149,*range(231,250)]]


    if magic:
        for ch in strMsg:
            rand_int = random.choice(accepted_colors_ints)
            color = fg(rand_int)
            try:
                res = attr(1)
                print(color+ch+res,end="")
            
            except:
                res = attr('reset')
                print(color+ch+res,end="")
    
    else:
        rand_int = random.choice(accepted_colors_ints)
        color = fg(rand_int)
        print(color+strMsg+attr(1))
    reset = attr('reset')    
    print (reset)
    


