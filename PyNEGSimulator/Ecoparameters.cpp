#include "Ecoparameters.h"

#define TIXML_USE_STL
#include <tinyxml_autolink.h>

#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace std;

#define LOAD_PARAM(paramName, paramType, defaultValue) \
	do{ \
		TiXmlElement* paramName##Elem = ecoParamsElem->FirstChildElement( #paramName );\
		if( paramName##Elem ){\
			try{\
				paramName = lexical_cast< paramType >( paramName##Elem ->GetText());\
			} catch(bad_lexical_cast&){ \
				paramName = defaultValue; \
			} \
		} else { \
			paramName = defaultValue;\
		}\
	} while (0);

void Ecoparameters::LoadFromXML(const string& xmlFileName)
{
	TiXmlDocument doc;
	doc.LoadFile(xmlFileName);
	
	TiXmlElement* ecoParamsElem = doc.FirstChildElement("Ecoparameters");
	
	TiXmlElement* alphaElem = ecoParamsElem->FirstChildElement("alpha");

	LOAD_PARAM(alpha, double, 0.08);
	LOAD_PARAM(beta, double, 0.8);
	LOAD_PARAM(delta, double, 0.4);
	LOAD_PARAM(gamma, double, 0.4);
	LOAD_PARAM(n, int, 0);
	LOAD_PARAM(L, double, 1.0);
	LOAD_PARAM(phi, double, 1.0);
	LOAD_PARAM(rho, double, 0.8);
	LOAD_PARAM(sigma, double, 0.001);
	LOAD_PARAM(sp, double, 0.5);
	LOAD_PARAM(tc, double, 1.1);
	LOAD_PARAM(w0, double, 1.0);
	LOAD_PARAM(grdstep, long, 1);
	LOAD_PARAM(shortit, int, 100);
	LOAD_PARAM(longit, int, 50);
}