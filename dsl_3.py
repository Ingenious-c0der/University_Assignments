class Matrix:
    
    def __init__(self, array):
        
       
        columns = list(set([len(array[i]) for i in range(len(array))]))
        if len(columns)==1:
            self.columns = columns[0]
            self.array = array
            self.rows = len(array)

        else:
            print("Invalid matrix")

    def add(self,array):
        try:
            matrix = Matrix(array)
            if self.rows == matrix.rows and self.columns == matrix.columns:
                res = [[0 for i in range(self.columns)] for i in range(self.rows)]
                for i in range(self.rows):
                    for j in range(self.columns):
                        res[i][j]=self.array[i][j] +matrix.array[i][j]
        
                return Matrix(res)
            else:
                print("Matrices with different dimensions given")
                return Matrix([["error"]])
        except:
            print("Invalid Matrices used")
            return Matrix([["error"]])

    def sub(self,array):
        try:
            matrix = Matrix(array)
            if self.rows == matrix.rows and self.columns == matrix.columns:
                res = [[0 for i in range(self.columns)] for i in range(self.rows)]
                for i in range(self.rows):
                    for j in range(self.columns):
                        res[i][j]=self.array[i][j] -matrix.array[i][j]
        
                return Matrix(res)
            else:
                print("Matrices with different dimensions given")
                return Matrix([["error"]])
        except:
            print("Invalid Matrices used")
            return Matrix([["error"]])

    def Transpose(self):
        """Returns the transpose of a matrix"""
        try:
            res = [[0 for i in range(self.rows)] for i in range(self.columns)]
            for i in range(self.rows):
                for j in range(self.columns):
                    res[j][i]=self.array[i][j]

            return Matrix(res)
        except:
            print("Invalid matrix given ")
            return Matrix([["error"]])
    def mul(self,array):
        try:
            matrix = Matrix(array)
            if self.columns == matrix.rows:
                res = [[0 for i in range(matrix.columns)] for i in range(self.rows)]
              
                for i in range(self.rows):
                    for j in range(matrix.columns):
                        for k in range(matrix.rows):
                            res[i][j] += self.array[i][k]*matrix.array[k][j]

                return Matrix(res)
            else:
                print("The given matrices cannot be multiplied")
                return Matrix([["error"]])
        except:
            print("Invalid matrix used")
            return Matrix([["error"]])
    def display_matrix(self):
        h = (self.columns*2-1)*" "
        
        print(f" _{h}_")
        for i in range(self.rows):
            for j in range(self.columns):
                if j==0:
                    print(f"| {self.array[i][j]} ",end="")
                elif j==self.columns-1:
                    print(f"{self.array[i][j]} |")
                else:
                    print(self.array[i][j],end=" ")

        print(f" ¯{h}¯")
   
    





if __name__ =="__main__":
    while True:
        choice = int(input("*****Menu*****\n1.Add matrices\n2.Multiply Matrices\n3.Subtract Matrices\n4.Find Transpose\n5.Exit\n"))
        if choice==5:break;
        r = int(input("Input the number of rows of the matrix : "))
        c = int(input("The number of columns of the matrix : "))
        l=[[int(input(f"Input the element for {j+1} row {i+1} column : ")) for i in range(c)] for j in range(r)]
        m = Matrix(l)
        print(" ------The given matrix is -----")
        m.display_matrix()

        
        if choice==1:
            r1 = int(input("Input the number of rows of the matrix : "))
            c1 = int(input("The number of columns of the matrix : "))
            l1=[[int(input(f"Input the element for {j+1} row {i+1} column : ")) for i in range(c1)] for j in range(r1)]
            m = Matrix(l)
            m1 = Matrix(l1)
            print(" ------The given matrix is -----")
            m1.display_matrix()
            print(" ------The output matrix is -----")
            x = m.add(l1)
            x.display_matrix()

        elif choice ==2:
            r1 = int(input("Input the number of rows of the matrix : "))
            c1 = int(input("The number of columns of the matrix : "))
            l1=[[int(input(f"Input the element for {j+1} row {i+1} column : ")) for i in range(c1)] for j in range(r1)]
          
            m1 = Matrix(l1)
            print(" ------The given matrix is -----")
            m1.display_matrix()
            print(" ------The output matrix is -----")
            m.mul(l1).display_matrix()

        elif choice ==3:
            r1 = int(input("Input the number of rows of the matrix : "))
            c1 = int(input("The number of columns of the matrix : "))
            l1=[[int(input(f"Input the element for {j+1} row {i+1} column : ")) for i in range(c1)] for j in range(r1)]
           
            m1 = Matrix(l1)
            print(" ------The given matrix is -----")
            m1.display_matrix()
            print(" ------The output matrix is -----")
            m.sub(l1).display_matrix()
        elif choice ==4:
         
            print(" ------The output matrix is -----")
            m.Transpose.display_matrix()
        else:
            print("Thankyou")
            break

        


