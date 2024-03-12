// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/* Two dimensional vector. */
template<class TType>
class FVector2D
{
public:
	FVector2D() : X(TType(0)), Y(TType(0)) {}

	/** Initialize X and Y with In */
	FVector2D(const TType In) 
		: X(In), Y(In)
	{
	}
	
	FVector2D(const TType InX, const TType InY) 
		: X(InX), Y(InY)
	{
	}

	template<typename TOldType>
	FVector2D(FVector2D<TOldType> OldVector) 
	{ 
		X = static_cast<TType>(OldVector.X); 
		Y = static_cast<TType>(OldVector.Y); 
	}

	template<typename TOldType>
	FVector2D& operator=(const FVector2D<TOldType> &OldVector) 
	{ 
		X = static_cast<TType>(OldVector.X); 
		Y = static_cast<TType>(OldVector.Y); 
		return *this; 
	}

	// Negate
	
	FVector2D operator-()
	{
		return FVector2D(-X, -Y);
	}
	FVector2D operator-() const
	{
		return FVector2D(-X, -Y);
	}

	// Basic calculations
	
	friend FVector2D operator+(const FVector2D<TType>& A, const FVector2D<TType>& B) 
	{ 
		return FVector2D<TType>(A.X + B.X, A.Y + B.Y); 
	}
	friend FVector2D operator-(const FVector2D<TType>& A, const FVector2D<TType>& B) 
	{
		return FVector2D<TType>(A.X - B.X, A.Y - B.Y); 
	}
	friend FVector2D operator*(const FVector2D<TType>& A, const FVector2D<TType>& B) 
	{ 
		return FVector2D<TType>(A.X * B.X, A.Y * B.Y); 
	}
	friend FVector2D operator/(const FVector2D<TType>& A, const FVector2D<TType>& B) 
	{ 
		return FVector2D<TType>(A.X / B.X, A.Y / B.Y); 
	}

	template <typename TOtherType>
	friend FVector2D operator+(const FVector2D<TOtherType>& L, const FVector2D<TType>& R) 
	{ 
		return FVector2D<TType>(static_cast<TType>(L.X) + R.X, static_cast<TType>(L.Y) + R.Y);
	}
	template <typename TOtherType>
	friend FVector2D operator-(const FVector2D<TOtherType>& L, const FVector2D<TType>& R) 
	{ 
		return FVector2D<TType>(static_cast<TType>(L.X) - R.X, static_cast<TType>(L.Y) - R.Y);
	}
	template <typename TOtherType>
	friend FVector2D operator*(const FVector2D<TOtherType>& L, const FVector2D<TType>& R) 
	{ 
		return FVector2D<TType>(static_cast<TType>(L.X) * R.X, static_cast<TType>(L.Y) * R.Y);
	}
	template <typename TOtherType>
	friend FVector2D operator/(const FVector2D<TOtherType>& L, const FVector2D<TType>& R) 
	{ 
		return FVector2D<TType>(static_cast<TType>(L.X) / R.X, static_cast<TType>(L.Y)/ R.Y);
	}

	FVector2D& operator+=(const FVector2D& V)
	{
		X += V.X; Y += V.Y; return *this;
	}
	FVector2D& operator-=(const FVector2D& V)
	{
		X -= V.X; Y -= V.Y; return *this;
	}
	FVector2D& operator*=(const FVector2D& V)
	{
		X *= V.X; Y *= V.Y; return *this;
	}
	FVector2D& operator/=(const FVector2D& V)
	{
		X /= V.X; Y /= V.Y; return *this;
	}

	// Comparison
	
	friend bool operator==(const FVector2D& L, const FVector2D& R)
	{
		return std::tie(L.X, L.Y) == std::tie(R.X, R.Y);
	}
	friend bool operator!=(const FVector2D& L, const FVector2D& R)
	{
		return !(L == R);
	}
	friend bool operator< (const FVector2D& L, const FVector2D& R)
	{
		return std::tie(L.X, L.Y) < std::tie(R.X, R.Y);
	}
	friend bool operator>=(const FVector2D& L, const FVector2D& R)
	{
		return !(L < R);
	}
	friend bool operator> (const FVector2D& L, const FVector2D& R)
	{
		return   R < L;
	}
	friend bool operator<=(const FVector2D& L, const FVector2D& R)
	{
		return !(R < L);
	}


	FVector2D& operator*=(const TType& V)
	{
		X *= V; Y *= V; return *this;
	}
	FVector2D& operator/=(const TType& V)
	{
		X /= V; Y /= V; return *this;
	}



	//FVector2D operator*(const TType& S, const FVector2D<TType>& V) { return FVector2D<TType>(V) *= S; }
	//FVector2D operator*(const FVector2D<TType>& V, const TType& S) { return FVector2D<TType>(V) *= S; }
	//FVector2D operator/(const TType& S, const FVector2D<TType>& V) { return FVector2D<TType>(V) /= S; }
	//FVector2D operator/(const FVector2D<TType>& V, const TType& S) { return FVector2D<TType>(V) /= S; }

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

	// Conversion
	operator SDL_Point() const
	{
		SDL_Point Point;
		Point.x = static_cast<int>(X);
		Point.y = static_cast<int>(Y);
		return Point;
	}

	operator std::ostream() const 
	{ 
		return "(" << X << ", " << Y << ")";
	}
	operator std::string() const 
	{ 
		return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")"; 
	}

	std::string ToString() const
	{
		return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
	}

public:
	TType X;
	TType Y;
};
