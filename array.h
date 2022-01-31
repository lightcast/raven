#include <iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;


#include <iomanip>
using std::setw;

#include <cstdlib>
using std::exit;

class Array
{
   friend ostream &operator<<( ostream &, const Array & );
   friend istream &operator>>( istream &, Array & );
public:
   Array( int = 10 );
   Array( const Array & );
   ~Array();
   int getSize() const;

   const Array &operator=( const Array & );
   bool operator==( const Array & ) const;

   bool operator!=( const Array &right ) const
   {
      return ! ( *this == right );
   }
   int &operator[]( int );

   int operator[]( int ) const;
private:
   int size;
   int *ptr;
};

Array::Array( int arraySize )
{
   size = arraySize;
   ptr = new int[ size ];

   for ( int i = 0; i < size; i++ )
      ptr[ i ] = 0;
}

Array::Array( const Array &arrayToCopy ) : size( arrayToCopy.size )
{
   ptr = new int[ size ];

   for ( int i = 0; i < size; i++ )
      ptr[ i ] = arrayToCopy.ptr[ i ];
}

Array::~Array()
{
   delete [] ptr;
}
int Array::getSize() const
{
   return size;
}

const Array &Array::operator=( const Array &right )
{
      delete [] ptr;
      size = right.size;
      ptr = new int[ size ];

      for ( int i = 0; i < size; i++ )
         ptr[ i ] = right.ptr[ i ];
   return *this;
}

bool Array::operator==( const Array &right ) const
{
   if ( size != right.size )
      return false;

   for ( int i = 0; i < size; i++ )
      if ( ptr[ i ] != right.ptr[ i ] )
         return false;

   return true;
}
int &Array::operator[]( int subscript )
{
   return ptr[ subscript ];
}
int Array::operator[]( int subscript ) const
{
   return ptr[ subscript ];
}
istream &operator>>( istream &input, Array &a )
{
   for ( int i = 0; i < a.size; i++ )
      input >> a.ptr[ i ];

   return input;
}
ostream &operator<<( ostream &output, const Array &a )
{
   int i;

   for ( i = 0; i < a.size; i++ ) {
      output << a.ptr[ i ];

   }
   return output;
}