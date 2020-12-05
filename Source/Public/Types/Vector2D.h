//

#pragma once

#include <Engine.PCH.h>

/* Two dimensional vector. */
template<class TType = float>
class Vector2D
{
public:
	Vector2D() : X(TType(0)), Y(TType(0)) {}

	Vector2D(const TType x, const TType y) 
		: X(x), Y(y) 
	{}

	template<typename TOldType>
	Vector2D(Vector2D<TOldType> OldVector) 
	{ 
		X = static_cast<TType>(OldVector.X); 
		Y = static_cast<TType>(OldVector.Y); 
	}

	// Comparsion
	template<typename TOldType>
	Vector2D operator=(const Vector2D<TOldType> &OldVector) 
	{ 
		X = static_cast<TType>(OldVector.X); 
		Y = static_cast<TType>(OldVector.Y); 
		return *this; 
	}

	// Set to negative value
	Vector2D operator-() const { return Vector2D(-X, -Y); }

	// Basic calculations
	friend Vector2D operator+(const Vector2D<TType>& v1, const Vector2D<TType>& v2) 
	{ 
		return Vector2D<TType>(v1.X + v2.X, v1.Y + v2.Y); 
	}
	friend Vector2D operator-(const Vector2D<TType>& v1, const Vector2D<TType>& v2) 
	{
		return Vector2D<TType>(v1.X - v2.X, v1.Y - v2.Y); 
	}
	friend Vector2D operator*(const Vector2D<TType>& v1, const Vector2D<TType>& v2) 
	{ 
		return Vector2D<TType>(v1.X * v2.X, v1.Y * v2.Y); 
	}
	friend Vector2D operator/(const Vector2D<TType>& v1, const Vector2D<TType>& v2) 
	{ 
		return Vector2D<TType>(v1.X / v2.X, v1.Y / v2.Y); 
	}

	template <typename TOthertype>
	friend Vector2D operator+(const Vector2D<TOthertype>& L, const Vector2D<TType>& R) 
	{ 
		return Vector2D<TType>(static_cast<TType>(L.X) + R.X, static_cast<TType>(L.Y) + R.Y);
	}
	template <typename TOthertype>
	friend Vector2D operator-(const Vector2D<TOthertype>& L, const Vector2D<TType>& R) 
	{ 
		return Vector2D<TType>(static_cast<TType>(L.X) - R.X, static_cast<TType>(L.Y) - R.Y);
	}
	template <typename TOthertype>
	friend Vector2D operator*(const Vector2D<TOthertype>& L, const Vector2D<TType>& R) 
	{ 
		return Vector2D<TType>(static_cast<TType>(L.X) * R.X, static_cast<TType>(L.Y) * R.Y);
	}
	template <typename TOthertype>
	friend Vector2D operator/(const Vector2D<TOthertype>& L, const Vector2D<TType>& R) 
	{ 
		return Vector2D<TType>(static_cast<TType>(L.X) / R.X, static_cast<TType>(L.Y)/ R.Y);
	}

	Vector2D& operator+=(const Vector2D& v) { X += v.X; Y += v.Y; return *this; }
	Vector2D& operator-=(const Vector2D& v) { X -= v.X; Y -= v.Y; return *this; }
	Vector2D& operator*=(const Vector2D& v) { X *= v.X; Y *= v.Y; return *this; }
	Vector2D& operator/=(const Vector2D& v) { X /= v.X; Y /= v.Y; return *this; }

	// Comparsion
	friend bool operator==(const Vector2D& L, const Vector2D& R) { return std::tie(L.X, L.Y) == std::tie(R.X, R.Y); }
	friend bool operator!=(const Vector2D& L, const Vector2D& R) { return !(L == R); }
	friend bool operator< (const Vector2D& L, const Vector2D& R) { return std::tie(L.X, L.Y) < std::tie(R.X, R.Y); }
	friend bool operator>=(const Vector2D& L, const Vector2D& R) { return !(L < R); }
	friend bool operator> (const Vector2D& L, const Vector2D& R) { return   R < L; }
	friend bool operator<=(const Vector2D& L, const Vector2D& R) { return !(R < L); }


	Vector2D& operator*=(const TType& V) { X *= V; Y *= V; return *this; }
	Vector2D& operator/=(const TType& V) { X /= V; Y /= V; return *this; }

	//Vector2D operator*(const TType& S, const Vector2D<TType>& V) { return Vector2D<TType>(V) *= S; }
	//Vector2D operator*(const Vector2D<TType>& V, const TType& S) { return Vector2D<TType>(V) *= S; }
	//Vector2D operator/(const TType& S, const Vector2D<TType>& V) { return Vector2D<TType>(V) /= S; }
	//Vector2D operator/(const Vector2D<TType>& V, const TType& S) { return Vector2D<TType>(V) /= S; }

	//template<class TType> TType DotProduct(const Vector2d<TType>&, const Vector2d<TType>&);
	//template<class TType> TType CrossProduct(const Vector2d<TType>&, const Vector2d<TType>&);

	////Returns the length of the vector from the origin.
	//template<class TType> TType EuclideanNorm(const Vector2d<TType>&);

	//// Return the unit vector of the input
	//template<class TType> Vector2d<TType> Normal(const Vector2d<TType>&);

	////Return a vector perpendicular to the left.
	//template<class TType> Vector2d<TType> Perpendicular(const Vector2d<TType>&);

	////Return true if two line segments intersect.
	//template<class TType> bool Intersect(const Vector2d<TType>&, const Vector2d<TType>&, const Vector2d<TType>&, const Vector2d<TType>&);

	////Return the point where two lines intersect.
	//template<class TType> Vector2d<TType> GetIntersect(const Vector2d<TType>&, const Vector2d<TType>&, const Vector2d<TType>&, const Vector2d<TType>&)
	

	// @Returns 0 - Should be rewritten into some kind of static.
	Vector2D& Zero() { X = TType(0); Y = TType(0); }

	// Conversion
	operator std::ostream () const 
	{ 
		//std::ostream stream = "(" + X + "," + Y + ")";
		return "(" + X + "," + Y + ")";
	}
	operator std::string () const 
	{ 
		return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; 
	}

public:
	TType X;
	TType Y;
};
