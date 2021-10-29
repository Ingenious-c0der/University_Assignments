#include <iostream>
using namespace std;

class Complex{
	float	real,img;
public:
	//Constructor
	Complex()
    {
		real=0.0;
		img = 0.0;
	}
	//Addition operator overloaded
	  Complex operator + (Complex O)
	{
		Complex temp;
		temp.real=real+O.real;
		temp.img= img+O.img;
		return temp;


	}
	//Multiplication operator overloaded
	Complex operator  * (Complex O)
	{
		Complex temp;
		temp.real = (real*O.real)-(img*O.img);
		temp.img= (real*O.img)+(img*O.real);
		return temp;


	}
	//Overloading increment operator
	Complex operator ++()
	{
		Complex temp;
		temp.real = real+1;
		temp.img = img +1 ;
		return temp;

	}







	//Overloading Subtraction Operator
	Complex operator - (Complex O)
	{
		Complex temp;
		temp.real = real-O.real;
		temp.img = img-O.img;
		return temp;
	}


	// Overloading extraction operator
	friend ostream  &operator <<  (ostream	&output,Complex O)
	// here we don't need to say Complex &O since O will take up the values for complex object passed in it.Here we don't need to change the value of
	// any object outside the function (like we need to in cin) but we only need to access the values here which are present in Complex O and can be
	// accessed by using O.img and O.real
	{

		if (O.img<0)
		{

			output<<O.real<<""<<O.img<<"i"<<endl;

		}
		else
		{

		output<<O.real<<"+"<<O.img<<"i"<<endl;

		}
		return	output;

	}
	//Overloading insertion operator
	friend istream  &operator >> (istream &input,Complex &O)
	{// now why do we need &O here and not in extraction operator function? The answer is - In cin we are assigning value to something outside the function which can
	// be done only using reference . Lets say we do not use . Then we get an complex object passed in O. when we assign , we pass the value to
		// O inside the function and not the object outside the function. So it won't work
		cout<<"Real	part:";
		input>>O.real;
		cout<<"Imaginary part:";
		input>>O.img;
		return input;
	}

	// Overloading exclamation operator for conjugate
	Complex operator ! ()
	{
		Complex temp;
		temp.real = real;
		temp.img = -img;
		return temp;
	}

	//Overloading division Operator
	Complex operator / (Complex C)
	{
		Complex temp ;
		Complex Conjugate = !(C);

		temp.real= ((real*C.real)+(img*Conjugate.img))/(C.real*C.real-Conjugate.img*C.img);
		temp.img = (img*C.real-Conjugate.img*real)/(C.real*C.real-Conjugate.img*C.img);

		return temp;

	}
};

int main() {
	int choice;
	bool exit_variable = false;
	while(not exit_variable){
	Complex c1,c2;
	cin>>c1;
	cin>>c2;
	cout<<"*****MENU*******"<<endl;
	cout<<"enter choice"<<endl;
	cout<<"1.Multiplication \n2.Addition \n3.Subtraction \n4.Conjugate \n5.Division \n6.Increment \n7.Exit"<<endl;
	cin>>choice;



	switch(choice){
	case 1:
		cout<<c1*c2<<endl;
		break;
	case 2:

		cout<<c1+c2<<endl;//similar to c1.add(c2)
		break;
	case 3:
		cout<<c1-c2<<endl;
		break;
	case 4:
		cout<<!(c1)<<endl;
		cout<<!(c2)<<endl;
		break;

	case 5:
		cout<<(c1/c2);
		break;

	case 6:
		cout<<++c1<<endl;
		cout<<++c2<<endl;
		break;
	case 7:
		cout<<"Thankyou"<<endl;
		exit_variable=true;

		break;

	}
	}
	return 0;
}
