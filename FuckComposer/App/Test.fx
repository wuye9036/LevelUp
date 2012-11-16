float4x4 WVP: WorldViewProjection;

struct VSPS{
	float4 wpos: SV_Position;
	float4 pos: TEXCOORD0;
};

float4 CreateShadowVS( float4 inPos : POSITION ): SV_Position{
	return mul( inPos, WVP );
}

float4 CreateShadowPS( float4 wpos: SV_Position ): SV_Target{
	return float4(wpos.xyz, 1.0);
}

VSPS RenderShadowVS( float4 inPos: POSITION ){
	VSPS ret;
	ret.wpos = mul( inPos, WVP );
	ret.pos = inPos;
	return ret;
}

float4 RenderShadowPS( VSPS input ): SV_Target{
	return float4( input.wpos.zzz, 1.0 );
}

DepthStencilState ShadowRenderDSS
{
	DepthEnable = TRUE;
	DepthFunc = LESS_EQUAL;
	StencilEnable = FALSE;
};

RasterizerState ShadowRenderRS{
	DepthBias = 0;
	SlopeScaledDepthBias = -100;
};

technique10 ShadowBiasTest{
	pass ShadowCreator{
		SetVertexShader( CompileShader( vs_4_0, CreateShadowVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, CreateShadowPS() ) );
		SetDepthStencilState( ShadowRenderDSS, 0 );
	}

	pass ShadowRenderer{
		SetVertexShader( CompileShader( vs_4_0, RenderShadowVS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, RenderShadowPS() ) );
		SetDepthStencilState( ShadowRenderDSS, 0 );
		SetRasterizerState( ShadowRenderRS );
	}
}