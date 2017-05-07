#include <memory>
#include <deque>
#include <iostream>
#include <iomanip>
struct Byte
{
    Byte( )
    {
        memset( this, 0, sizeof( Byte ) );
    }
    Byte( unsigned char const& other )
    {
        memcpy( this, &other, sizeof( unsigned char ) );
    }
    Byte( Byte const& other )
    {
        memcpy( this, &other, sizeof( unsigned char ) );
    }
    Byte operator^( Byte const& right ) const
    {
        Byte ret;
        unsigned char l = *( unsigned char* )this;
        unsigned char r = *(unsigned char*)&right;
        unsigned char calced = l ^ r;
        memcpy( &ret, &calced, sizeof( unsigned char ) );
        return ret;
    }
    Byte operator&( Byte const& right ) const
    {
        Byte ret;
        unsigned char l = *( unsigned char* )this;
        unsigned char r = *(unsigned char*)&right;
        unsigned char calced = l & r;
        memcpy( &ret, &calced, sizeof( unsigned char ) );
        return ret;
    }
    Byte operator|( Byte const& right ) const
    {
        Byte ret;
        unsigned char l = *( unsigned char* )this;
        unsigned char r = *(unsigned char*)&right;
        unsigned char calced = l | r;
        memcpy( &ret, &calced, sizeof( unsigned char ) );
        return ret;
    }
    Byte operator~( ) const
    {
        Byte ret;
        unsigned char l = *( unsigned char* )this;
        unsigned char calced = ~l;
        memcpy( &ret, &calced, sizeof( unsigned char ) );
        return ret;
    }
    friend std::ostream &operator<<( std::ostream &dest, Byte const& value )
    {
        return dest << std::hex << std::setfill( '0' ) << std::setw( 2 ) << ( size_t )*(unsigned char*)( &value );
    }
    bool a : 1;
    bool b : 1;
    bool c : 1;
    bool d : 1;
    bool e : 1;
    bool f : 1;
    bool g : 1;
    bool h : 1;
};
template <const size_t BIT, const size_t BYTE = BIT / 8>
class BigBit
{
private:
    Byte data[BYTE];
public:
    BigBit( )
    {
    }
    BigBit( size_t value )
    {
        memcpy( this, &value, sizeof( size_t ) );
    }
    BigBit( BigBit const& other )
    {
        memcpy( this, &other, sizeof( BigBit ) );
    }
    BigBit& operator=( BigBit const& right )
    {
        memcpy( this, &right, sizeof( BigBit ) );
        return *this;
    }
    BigBit operator^( BigBit const& right ) const
    {
        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i] = data[i] ^ right.data[i];
        }
        return ret;
    }
    BigBit operator&( BigBit const& right ) const
    {
        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i] = data[i] & right.data[i];
        }
        return ret;
    }
    BigBit operator|( BigBit const& right ) const
    {
        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i] = data[i] | right.data[i];
        }
        return ret;
    }
    BigBit operator~( ) const
    {
        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i] = ~data[i];
        }
        return ret;
    }
    BigBit operator<<( size_t right )const
    {
        std::deque<bool> deque;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            deque.push_back( data[i].a );
            deque.push_back( data[i].b );
            deque.push_back( data[i].c );
            deque.push_back( data[i].d );
            deque.push_back( data[i].e );
            deque.push_back( data[i].f );
            deque.push_back( data[i].g );
            deque.push_back( data[i].h );
        }
        for ( size_t i = 0; i < right; ++i )
        {
            deque.pop_back( );
            deque.push_front( 0 );
        }

        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i].a = deque[i * 8 + 0];
            ret.data[i].b = deque[i * 8 + 1];
            ret.data[i].c = deque[i * 8 + 2];
            ret.data[i].d = deque[i * 8 + 3];
            ret.data[i].e = deque[i * 8 + 4];
            ret.data[i].f = deque[i * 8 + 5];
            ret.data[i].g = deque[i * 8 + 6];
            ret.data[i].h = deque[i * 8 + 7];
        }
        return ret;
    }
    BigBit operator>>( size_t right )const
    {
        std::deque<bool> deque;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            deque.push_back( data[i].a );
            deque.push_back( data[i].b );
            deque.push_back( data[i].c );
            deque.push_back( data[i].d );
            deque.push_back( data[i].e );
            deque.push_back( data[i].f );
            deque.push_back( data[i].g );
            deque.push_back( data[i].h );
        }
        for ( size_t i = 0; i < right; ++i )
        {
            deque.pop_front( );
            deque.push_back( deque.front( ) );
        }

        BigBit ret;
        for ( size_t i = 0; i < BYTE; ++i )
        {
            ret.data[i].a = deque[i * BYTE + 0];
            ret.data[i].b = deque[i * BYTE + 1];
            ret.data[i].c = deque[i * BYTE + 2];
            ret.data[i].d = deque[i * BYTE + 3];
            ret.data[i].e = deque[i * BYTE + 4];
            ret.data[i].f = deque[i * BYTE + 5];
            ret.data[i].g = deque[i * BYTE + 6];
            ret.data[i].h = deque[i * BYTE + 7];
        }
        return ret;
    }
    // http://www.c-lang.net/memcmp/index.html
    bool operator==( BigBit const& right ) const
    {
        return memcmp( this, &right, sizeof( BigBit ) ) == 0;
    }
    bool operator<( BigBit const& right ) const
    {
        for ( size_t ri = BYTE - 1; ri >= 0; --ri )
        {
            if ( *( unsigned char* )&this->data[ri] == *(unsigned char*)&right.data[ri] ) continue;
            return *( unsigned char* )&this->data[ri] < *(unsigned char*)&right.data[ri];
        }
        return false;
    }
    bool operator>( BigBit const& right ) const
    {
        for ( size_t ri = BYTE - 1; ri >= 0; --ri )
        {
            if ( *( unsigned char* )&this->data[ri] == *(unsigned char*)&right.data[ri] ) continue;
            return *( unsigned char* )&this->data[ri] > *(unsigned char*)&right.data[ri];
        }
        return false;
    }
    bool operator<=( BigBit const& right ) const
    {
        for ( size_t ri = BYTE - 1; ri >= 0; --ri )
        {
            if ( *( unsigned char* )&this->data[ri] == *(unsigned char*)&right.data[ri] ) continue;
            return *( unsigned char* )&this->data[ri] <= *(unsigned char*)&right.data[ri];
        }
        return false;
    }
    bool operator>=( BigBit const& right ) const
    {
        for ( size_t ri = BYTE - 1; ri >= 0; --ri )
        {
            if ( *( unsigned char* )&this->data[ri] == *(unsigned char*)&right.data[ri] ) continue;
            return *( unsigned char* )&this->data[ri] >= *(unsigned char*)&right.data[ri];
        }
        return false;
    }
    // https://www.kaoriya.net/blog/2013/02/04/
    BigBit operator+( BigBit const& right ) const
    {
        BigBit a = *this;
        BigBit b = right;
        while ( true )
        {
            BigBit c = a ^ b;
            BigBit d = a & b;
            BigBit e = d << 1;
            if ( e == BigBit( 0 ) ) return c;
            a = c;
            b = e;
        }
    }
    // http://ednjapan.com/edn/articles/1307/16/news002.html
    BigBit operator-( BigBit const& right ) const
    {
        return ~( ~*this + right );
    }
    // http://ednjapan.com/edn/articles/1307/16/news002.html
    BigBit operator*( BigBit const& right ) const
    {
        BigBit ret;
        for ( size_t i = 0; i < BIT; ++i )
        {
            if ( ( right & ( BigBit( 1 ) << i ) ) == ( BigBit( 1 ) << i ) )
            {
                ret = ret + ( *this << i );
            }
        }
        return ret;
    }
    // http://akademeia.info/index.php?%B3%E4%A4%EA%BB%BB%BD%E8%CD%FD
    BigBit operator/( BigBit const& right ) const
    {
        BigBit count( 1 );
        BigBit calc = *this - right;
        while ( calc >= right )
        {
            calc = calc - right;
            count = count + BigBit( 1 );
        }
        return count;
    }
    BigBit operator%( BigBit const& right ) const
    {
        BigBit count( 1 );
        BigBit calc = *this - right;
        while ( calc >= right )
        {
            calc = calc - right;
            count = count + BigBit( 1 );
        }
        return calc;
    }
    friend std::ostream &operator<<( std::ostream &dest, BigBit const& value )
    {
        size_t ri;
        for ( ri = BYTE - 1; ri >= 1; --ri )
        {
            dest << value.data[ri];
            if ( ( ri & 0x1 ) == 0x0 ) dest << ':';
        }
        dest << value.data[ri];
        return dest;
    }
};
int main( int argumentCount, char** argumentVector )
{
    std::cout << "4294967295 + 9854452 --> 4304821747(0000:0001:0096:5df3)" << std::endl 
        << BigBit<256>( 4294967295 ) + BigBit<256>( 9854452 ) << std::endl;
    std::cout << "4294967295 - 9854452 --> 4285112843(0000:0000:ff69:a20b)" << std::endl 
        << BigBit<256>( 4294967295 ) - BigBit<256>( 9854452 ) << std::endl;
    std::cout << "4294967295 * 9854452 --> 42324549050147340(0096:5df3:ff69:a20c)" << std::endl 
        << BigBit<256>( 4294967295 ) * BigBit<256>( 9854452 ) << std::endl;
    std::cout << "4294967295 / 9854452 --> 435(0000:0000:0000:01b3)" << std::endl 
        << BigBit<256>( 4294967295 ) / BigBit<256>( 9854452 ) << std::endl;
    return 0;
}