#include "TypeCode.h"
#include "cstrext.h"

BuildinTypeSpec GetComponentType(BuildinTypeSpec type){
	return type & BT_BaseMask;
}

BuildinTypeSpec GenVecType(BuildinTypeSpec base, int len){
	return base | ((len-1) << 8) | BT_Vector;
}

BuildinTypeSpec GenMatType(BuildinTypeSpec base, int len1, int len2){
	return base | ((len1-1) << 8) | (len2-1) | BT_Matrix;
}

bool IsVectorType(BuildinTypeSpec type)
{
	return (type & BT_TemplateMask) == BT_Vector;
}

bool IsMatrxiType(BuildinTypeSpec type)
{
	return (type & BT_TemplateMask) == BT_Matrix;
}

int VectorSize(BuildinTypeSpec typeSpec) {
	return ((typeSpec & BT_1stDimMask) >> 8) + 1;
}

void MatrixSize(BuildinTypeSpec typeSpec, int& size1d, int& size2d)
{
	size1d = ((typeSpec & BT_1stDimMask) >> 8) + 1;
	size2d = (typeSpec & BT_2ndDimMask) + 1;
}

bool IsStructType(BuildinTypeSpec typeSpec)
{
	return (typeSpec & BT_BaseMask) == BT_Struct;
}

bool IsUserType(BuildinTypeSpec typeSpec)
{
	return (typeSpec & BT_BaseMask) == BT_UserType;
}

using namespace std;

string BuildinTypeToString(BuildinTypeSpec typeSpec)
{
	string retStr;
	switch (GetComponentType(typeSpec))
	{
		case BT_Void:
			retStr.assign("void");
			break;
		case BT_Int:
			retStr.assign("int");
			break;
		case BT_UInt:
			retStr.assign("uint");
			break;
		case BT_Half:
			retStr.assign("half");
			break;
		case BT_Float:
			retStr.assign("float");
			break;
		case BT_Double:
			retStr.assign("double");
			break;
		case BT_Boolean:
			retStr.assign("boolean");
			break;
		case BT_Struct:
		case BT_UserType:
			break;
		default:
			return retStr;
	}

	if(IsVectorType(typeSpec))
	{
		retStr.append(1, (char)(VectorSize(typeSpec)) + '0');
	}

	if(IsMatrxiType(typeSpec))
	{
		int _1stDimSize, _2ndDimSize;
		MatrixSize(typeSpec, _1stDimSize, _2ndDimSize);
		retStr.append(format("%dx%d", _1stDimSize, _2ndDimSize));
	}

	retStr.append(" ");

	return retStr;
}

string TypeQualToString(type_qualifier typeQual)
{
	string retStr;

	if(typeQual.HasQual(TQ_Shared)){
		retStr += "shared ";
	}
	if(typeQual.HasQual(TQ_Volatile)){
		retStr += "volatile ";
	}
	if(typeQual.HasQual(TQ_Const)){
		retStr += "const ";
	}
	if(typeQual.HasQual(TQ_Uniform)){
		retStr += "uniform ";
	}
	if(typeQual.HasQual(TQ_NoInteroperation)){
		retStr += "nointeroperation ";
	}

	return retStr;
}

string StorageTypeToString(storage_type st)
{
	switch (st)
	{
		case ST_Extern:
			return string("extern ");
		case ST_Static:
			return string("static ");
		case ST_Typedef:
			return string("typedef ");
		default:
			break;
	}

	return string("");
}
