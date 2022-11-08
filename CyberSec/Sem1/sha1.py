import hashlib 

str = input("Enter the string to be encoded :")

result = hashlib.sha1(str.encode())

print(f"The hash is : {result.hexdigest()}")
