#define ARMA_DONT_PRINT_ERRORS
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
  {
	mat x(4, 1, fill::zeros);
	mat x_current(4, 1, fill::zeros);
	mat P(4, 4, fill::zeros);
	mat P_current(4, 4, fill::zeros);
	mat y(2, 1, fill::zeros);
	mat S(2, 2, fill::zeros);
	mat K(4, 2, fill::zeros);
	
	mat F(4, 4, fill::zeros);
	mat B(4, 3, fill::zeros);
	mat u(3, 1, fill::zeros);
	mat Q(4, 4, fill::zeros);
	mat z(2, 1, fill::zeros);
	mat H(2, 4, fill::zeros);
	mat R(2, 2, fill::zeros);
	

	x = (F * x_current) + (B * u);					// Predict
	P = ( F * P_current * F.t() ) + Q;				// Predict
	
	y = z - (H * x);								// Update
	S = ( H * P * H.t() ) + R;						// Update
	try{
		// if inv(): matrix appears to be singular, then set K to 
		K = P * H.t() * S.i();						// Update
	}
	
	catch (exception& e){
		K.zeros();
	}
	x_current = x + (K * y);						// Update
	P_current = (eye<mat>(4,4) - (K * H)) * P;		// Update
	
	K.print();
  
  return 0;
  }
