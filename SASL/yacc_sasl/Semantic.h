#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

/*****************************************
SemanticType [Usage] = SemanticSpec
*****************************************/
enum SemanticType {
    SMT_None = 0,
    //VS Input
    SMT_Binormal,
    SMT_BlendIndices,
    SMT_BlendWeight,
    SMT_Color,			//VS Input, VS Output, PS Input, PS Output
    SMT_Normal,
    SMT_Position,		//VS Input, VS Output
    SMT_PositionT,
    SMT_PSize,			//VS Output
    SMT_Tangent,
    SMT_Texcoord,		//VS Input, VS Output, PS Input

    //VS Output
    SMT_Fog,
    SMT_TessFactor,

    //PS Input
    SMT_VFace,
    SMT_VPos,

    //PS Output
    SMT_Depth,

    //DX10
    SMT_SV_ClipDistance,
    SMT_SV_CullDistance,
    SMT_SV_Coverage,
    SMT_SV_IsFrontFace,
    SMT_SV_Position,
    SMT_SV_RenderTargetArrayIndex,
    SMT_SV_SampleIndex,
    SMT_SV_Target,
    SMT_SV_ViewPortArrayIndex,
    SMT_SV_InstanceID,
    SMT_SV_PrimitiveID,
    SMT_SV_VertexID
};

typedef unsigned int Semantic;

inline SemanticType GetSemanticType(Semantic smt) {
    return static_cast<SemanticType>(smt & 0x0000FFFF);
}

inline bool IsSemanticType(Semantic smt, SemanticType SMT) {
    return SMT == GetSemanticType(smt);
}

inline int GetSemanticUsage(Semantic smt) {
    return static_cast<int>( (smt & 0xFFFF0000) >> 16);
}

inline Semantic GetSemantic(SemanticType SMT, int usage) {
    if (usage < 0) return 0;
    return static_cast<Semantic>(SMT | (usage << 16));
}

inline std::string SemanticToString(Semantic semantic) {
    SemanticType smt;
    std::string retStr = "";
    switch (smt) {
    case SMT_None:
        break;
    case SMT_Binormal:
		retStr = "BINORMAL";
		break;
    case SMT_BlendIndices:
        retStr = "BLENDINDICES ";
        break;
    case SMT_BlendWeight:
        retStr = "BLENDWEIGHT ";
        break;
    case SMT_Color:
        retStr = "COLOR ";
        break;
    case SMT_Normal:
        retStr = "NORMAL ";
        break;
    case SMT_Position:
        retStr = "POSITION ";
        break;
    case SMT_PositionT:
        retStr = "POSITIONT ";
        break;
    case SMT_PSize:
        retStr = "PSIZE ";
        break;
    case SMT_Tangent:
        retStr = "TANGENT ";
        break;
    case SMT_Texcoord:
        retStr = "TEXCOORD ";
        break;
    case SMT_Fog:
        retStr = "FOG ";
        break;
    case SMT_TessFactor:
        retStr = "TESSFACTOR ";
        break;
    case SMT_VFace:
        retStr = "VFACE ";
        break;
    case SMT_VPos:
        retStr = "VPOS ";
        break;
    case SMT_Depth:
        retStr = "DEPTH ";
        break;
    case SMT_SV_ClipDistance:
        retStr = "SV_ClipDistance ";
        break;
    case SMT_SV_CullDistance:
        retStr = "SV_CullDistance ";
        break;
    case SMT_SV_Coverage:
        retStr = "SV_Coverage ";
        break;
    case SMT_SV_IsFrontFace:
        retStr = "SV_IsFrontFace ";
        break;
    case SMT_SV_Position:
        retStr = "SV_Position ";
        break;
    case SMT_SV_RenderTargetArrayIndex:
        retStr = "SV_RenderTargetArrayIndex ";
        break;
    case SMT_SV_SampleIndex:
        retStr = "SV_SampleIndex ";
        break;
    case SMT_SV_Target:
        retStr = "SV_Target ";
        break;
    case SMT_SV_ViewPortArrayIndex:
        retStr = "SV_ViewPortArrayIndex ";
        break;
    case SMT_SV_InstanceID:
        retStr = "SV_InstanceID ";
        break;
    case SMT_SV_PrimitiveID:
        retStr = "SV_PrimitiveID ";
        break;
    default:
        retStr = " ";
        break;
    }
    return retStr;
}
#endif // SEMANTIC_H_INCLUDED
