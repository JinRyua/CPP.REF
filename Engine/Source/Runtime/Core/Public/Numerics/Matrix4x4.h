// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include "Mathematics/TAngleDef.h"

struct Vector3;
struct Vector4;
struct Quaternion;

#pragma pack(push, 4)
/// <summary>
/// 4x4 행렬을 표현합니다.
/// </summary>
struct CORE_API Matrix4x4 : public TNumericsBasicOperator<Matrix4x4, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float>
{
    using This = Matrix4x4;

    /// <summary>
    /// 1행 1열 값을 나타냅니다.
    /// </summary>
    float _11;

    /// <summary>
    /// 1행 2열 값을 나타냅니다.
    /// </summary>
    float _12;

    /// <summary>
    /// 1행 3열 값을 나타냅니다.
    /// </summary>
    float _13;

    /// <summary>
    /// 1행 4열 값을 나타냅니다.
    /// </summary>
    float _14;

    /// <summary>
    /// 2행 1열 값을 나타냅니다.
    /// </summary>
    float _21;

    /// <summary>
    /// 2행 2열 값을 나타냅니다.
    /// </summary>
    float _22;

    /// <summary>
    /// 2행 3열 값을 나타냅니다.
    /// </summary>
    float _23;

    /// <summary>
    /// 2행 4열 값을 나타냅니다.
    /// </summary>
    float _24;

    /// <summary>
    /// 3행 1열 값을 나타냅니다.
    /// </summary>
    float _31;

    /// <summary>
    /// 3행 2열 값을 나타냅니다.
    /// </summary>
    float _32;

    /// <summary>
    /// 3행 3열 값을 나타냅니다.
    /// </summary>
    float _33;

    /// <summary>
    /// 3행 4열 값을 나타냅니다.
    /// </summary>
    float _34;

    /// <summary>
    /// 4행 1열 값을 나타냅니다.
    /// </summary>
    float _41;

    /// <summary>
    /// 4행 2열 값을 나타냅니다.
    /// </summary>
    float _42;

    /// <summary>
    /// 4행 3열 값을 나타냅니다.
    /// </summary>
    float _43;

    /// <summary>
    /// 4행 4열 값을 나타냅니다.
    /// </summary>
    float _44;

    /// <summary>
    /// 개체를 초기화합니다.
    /// </summary>
    Matrix4x4();

    /// <summary>
    /// 개체를 초기화합니다.
    /// </summary>
    /// <param name="_11"> 1행 1열 값을 전달합니다. </param>
    /// <param name="_12"> 1행 2열 값을 전달합니다. </param>
    /// <param name="_13"> 1행 3열 값을 전달합니다. </param>
    /// <param name="_14"> 1행 4열 값을 전달합니다. </param>
    /// <param name="_21"> 2행 1열 값을 전달합니다. </param>
    /// <param name="_22"> 2행 2열 값을 전달합니다. </param>
    /// <param name="_23"> 2행 3열 값을 전달합니다. </param>
    /// <param name="_24"> 2행 4열 값을 전달합니다. </param>
    /// <param name="_31"> 3행 1열 값을 전달합니다. </param>
    /// <param name="_32"> 3행 2열 값을 전달합니다. </param>
    /// <param name="_33"> 3행 3열 값을 전달합니다. </param>
    /// <param name="_34"> 3행 4열 값을 전달합니다. </param>
    /// <param name="_41"> 4행 1열 값을 전달합니다. </param>
    /// <param name="_42"> 4행 2열 값을 전달합니다. </param>
    /// <param name="_43"> 4행 3열 값을 전달합니다. </param>
    /// <param name="_44"> 4행 4열 값을 전달합니다. </param>
    Matrix4x4(float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24, float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44);

    /// <summary>
    /// 개체를 초기화합니다.
    /// </summary>
    /// <param name="v1"> 1행 값을 전달합니다. </param>
    /// <param name="v2"> 2행 값을 전달합니다. </param>
    /// <param name="v3"> 3행 값을 전달합니다. </param>
    /// <param name="v4"> 4행 값을 전달합니다. </param>
    Matrix4x4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);

    /// <summary>
    /// 개체를 초기화합니다.
    /// </summary>
    /// <param name="copy"> 초기화 값을 전달합니다. </param>
    Matrix4x4(const Matrix4x4& copy);

    /// <summary>
    /// 대상 행렬과 같은지 비교합니다.
    /// </summary>
    /// <param name="rh"> 대상 개체를 전달합니다. </param>
    /// <returns> 비교 결과가 반환됩니다. </returns>
    bool Equals(const Matrix4x4& rh) const;

    /// <summary>
    /// 대상 행렬과 같은지 비교합니다.
    /// </summary>
    /// <param name="rh"> 대상 개체를 전달합니다. </param>
    /// <param name="epsilon"> 비교 오차를 전달합니다. </param>
    /// <returns> 비교 결과가 반환됩니다. </returns>
    bool NearlyEquals(const Matrix4x4& rh, float epsilon) const;

    /// <summary>
    /// 해시 코드 값을 가져옵니다.
    /// </summary>
    /// <returns> 값이 반환됩니다. </returns>
    size_t GetHashCode() const;

    /// <summary>
    /// 개체의 간단한 설명을 텍스트 형식으로 가져옵니다.
    /// </summary>
    /// <returns> 텍스트 개체가 반환됩니다. </returns>
    SString* ToString() const;

    /// <summary>
    /// 컴포넌트 값을 가져옵니다.
    /// </summary>
    /// <param name="index"> 컴포넌트 위치를 전달합니다. </param>
    /// <returns> 값이 반환됩니다. </returns>
    Vector4 GetComponentOrDefault(size_t index) const;

    /// <summary>
    /// 행렬 형식에거 값을 생성합니다.
    /// </summary>
    /// <param name="matrix"> 행렬 형식을 전달합니다. </param>
    template<TIsMatrixType T>
    inline void Construct(const T& matrix);

    /// <summary>
    /// 행렬 형식으로 변환합니다.
    /// </summary>
    /// <returns> 변환된 행렬 형식 값이 반환됩니다. </returns>
    template<TIsMatrixType T>
    inline T Cast() const;

    /// <summary>
    /// 해당 인덱스가 포함되어 있는지 검사합니다.
    /// </summary>
    /// <param name="index"> 인덱스를 전달합니다. </param>
    /// <returns> 검사 결과가 반환됩니다. </returns>
    bool Contains(size_t index) const;

    /// <summary>
    /// 해당 행렬 인덱스가 포함되어 있는지 검사합니다.
    /// </summary>
    /// <param name="row"> 행 인덱스를 전달합니다. </param>
    /// <param name="column"> 열 인덱스를 전달합니다. </param>
    /// <returns> 검사 결과가 반환됩니다. </returns>
    bool Contains(size_t row, size_t column) const;

    /// <summary>
    /// 컴포넌트 개수를 가져옵니다.
    /// </summary>
    /// <returns> 개수가 반환됩니다. </returns>
    size_t GetCount() const { return 16; }

    /// <summary>
    /// 행 개수를 가져옵니다.
    /// </summary>
    /// <returns> 개수가 반환됩니다. </returns>
    size_t GetNumRows() const { return 4; }

    /// <summary>
    /// 열 개수를 가져옵니다.
    /// </summary>
    /// <returns> 개수가 반환됩니다. </returns>
    size_t GetNumColumns() const { return 4; }

    /// <summary>
    /// 이 행렬을 전치행렬로 만듭니다.
    /// </summary>
    /// <returns> 작업 체인이 반환됩니다. </returns>
    Matrix4x4& Transpose();

    /// <summary>
    /// 이 행렬을 역행렬로 만듭니다.
    /// </summary>
    /// <returns> 작업 체인이 반환됩니다. </returns>
    Matrix4x4& Invert();

    /// <summary>
    /// 벡터를 변환합니다.
    /// </summary>
    /// <param name="vec"> 벡터를 전달합니다. </param>
    /// <param name="bCoord"> 위치 벡터인지 나타내는 값을 전달합니다. </param>
    /// <returns> 변환된 벡터가 반환됩니다. </returns>
    Vector3 TransformVector(const Vector3& vec, bool bCoord = true) const;

    /// <summary>
    /// 벡터를 변환합니다.
    /// </summary>
    /// <param name="vec"> 벡터를 전달합니다. </param>
    /// <returns> 변환된 벡터가 반환됩니다. </returns>
    Vector4 TransformVector(const Vector4& vec) const;

    /// <summary>
    /// 이 행렬이 단위행렬인지 검사합니다.
    /// </summary>
    /// <returns> 검사 결과가 반환됩니다. </returns>
    bool IsIdentity() const;

    /// <summary>
    /// 행렬의 행렬식 값을 계산합니다.
    /// </summary>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    float GetDeterminant() const;

    /// <summary>
    /// 행렬의 역행렬을 가져옵니다.
    /// </summary>
    /// <returns> 역행렬이 반환됩니다. </returns>
    Matrix4x4 GetInverse() const;

    /// <summary>
    /// 행렬의 전치행렬을 가져옵니다.
    /// </summary>
    /// <returns> 전치행렬이 반환됩니다. </returns>
    Matrix4x4 GetTransposed() const;

    /// <summary>
    /// 행렬을 이동, 비례, 회전값으로 분해합니다.
    /// </summary>
    /// <param name="outTranslation"> 이동 벡터를 받을 참조를 전달합니다. </param>
    /// <param name="outScale"> 비례 벡터를 받을 참조를 전달합니다. </param>
    /// <param name="outRotation"> 회전 사원수를 받을 참조를 전달합니다. </param>
    void BreakTransform(Vector3& outTranslation, Vector3& outScale, Quaternion& outRotation) const;

    /// <summary>
    /// 이동 벡터를 가져옵니다.
    /// </summary>
    /// <returns> 값이 반환됩니다. </returns>
    Vector3 GetTranslation() const;

    /// <summary>
    /// 비례 벡터를 가져옵니다.
    /// </summary>
    /// <returns> 값이 반환됩니다. </returns>
    Vector3 GetScale() const;
    /// <summary>
    /// 회전 사원수를 가져옵니다.
    /// </summary>
    /// <returns> 값이 반환됩니다. </returns>
    Quaternion GetRotation() const;

    const Vector4& operator [](size_t index) const;
    Vector4& operator [](size_t index);

    Matrix4x4 operator -() const;
    Matrix4x4 operator +(const Matrix4x4& right) const;
    Matrix4x4 operator -(const Matrix4x4& right) const;
    Matrix4x4 operator *(const Matrix4x4& right) const;
    Matrix4x4 operator /(const Matrix4x4& right) const;

    Matrix4x4& operator +=(const Matrix4x4& right);
    Matrix4x4& operator -=(const Matrix4x4& right);
    Matrix4x4& operator *=(const Matrix4x4& right);
    Matrix4x4& operator /=(const Matrix4x4& right);

    /// <summary>
    /// 두 행렬을 곱합니다.
    /// </summary>
    /// <param name="a"> 첫 번째 값을 전달합니다. </param>
    /// <param name="b"> 두 번째 값을 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b);

    /// <summary>
    /// 카메라가 세계를 바라보는 행렬을 계산합니다.
    /// </summary>
    /// <param name="location"> 카메라 위치를 전달합니다. </param>
    /// <param name="dir"> 카메라가 바라보는 방향을 전달합니다.</param>
    /// <param name="up"> 카메라 방향의 상향 벡터를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 LookTo(const Vector3& location, const Vector3& dir, const Vector3& up);

    /// <summary>
    /// 이동, 비례, 회전에 대한 아핀 변환을 계산합니다.
    /// </summary>
    /// <param name="t"> 이동 벡터를 전달합니다. </param>
    /// <param name="s"> 비례 벡터를 전달합니다. </param>
    /// <param name="q"> 회전 사원수를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 AffineTransformation(const Vector3& t, const Vector3& s, const Quaternion& q);

    /// <summary>
    /// 원근 투영 행렬을 계산합니다.
    /// </summary>
    /// <param name="fov"> 시야각 값을 전달합니다. </param>
    /// <param name="aspectRatio"> 종횡비 값을 전달합니다. </param>
    /// <param name="nearZ"> 가까운 평면의 거리를 전달합니다. </param>
    /// <param name="farZ"> 먼 평면의 거리를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 PerspectiveFovLH(float fov, float aspectRatio, float nearZ, float farZ);

    /// <summary>
    /// 직교 투영 행렬을 계산합니다.
    /// </summary>
    /// <param name="inWidth"> 뷰 너비를 전달합니다. </param>
    /// <param name="inHeight"> 뷰 높이를 전달합니다. </param>
    /// <param name="nearZ"> 가까운 평면의 거리를 전달합니다. </param>
    /// <param name="farZ"> 먼 평면의 거리를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 OrthographicLH(float inWidth, float inHeight, float nearZ, float farZ);

    /// <summary>
    /// X축 회전 행렬을 계산합니다.
    /// </summary>
    /// <param name="angle"> 회전 각도를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 RotationX(TRadians<float> angle);

    /// <summary>
    /// Y축 회전 행렬을 계산합니다.
    /// </summary>
    /// <param name="angle"> 회전 각도를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 RotationY(TRadians<float> angle);

    /// <summary>
    /// Z축 회전 행렬을 계산합니다.
    /// </summary>
    /// <param name="angle"> 회전 각도를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 RotationZ(TRadians<float> angle);

    /// <summary>
    /// 축 회전 행렬을 계산합니다.
    /// </summary>
    /// <param name="inAxis"> 축 벡터를 전달합니다. </param>
    /// <param name="angle"> 회전 각도를 전달합니다. </param>
    /// <returns> 계산 결과가 반환됩니다. </returns>
    static Matrix4x4 RotationNormal(const Vector3& inAxis, TRadians<float> angle);

    /// <summary>
    /// 단위행렬을 나타냅니다.
    /// </summary>
    static Matrix4x4 Identity;
};
#pragma pack(pop)

#include "Matrix4x4.inl"