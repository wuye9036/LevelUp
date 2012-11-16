#ifdef INIT_SEMIAUTO_REGTYPE
	#include <boost/preprocessor/slot/counter.hpp>
	#ifdef BOOST_PP_COUNTER
		#undef BOOST_PP_COUNTER
	#endif
	#define BOOST_PP_COUNTER 0
	#undef INIT_SEMIAUTO_REGTYPE
	#define EXECUTE_SEMIAUTO_REGTYPE
#else
	#ifdef FIN_SEMIAUTO_REGTYPE
		#undef EXECUTE_SEMIAUTP_REGTYPE
		#undef FIN_SEMIAUTO_REGTYPE
		#undef TYPE_PARAM
		#undef BOOST_PP_COUNTER
		#ifdef ENUM_NAME_AUTOGEN
			#undef ENUM_NAME_AUTOGEN
		#endif
	#else
		#ifdef EXECUTE_SEMIAUTO_REGTYPE
			#ifndef TYPE_PARAM
				#error must has a type for registering!
			#endif
			#include BOOST_PP_UPDATE_COUNTER()
			template<> struct type_encode<TYPE_PARAM>{static const type_id id = BOOST_PP_COUNTER; };
			template<> struct type_decode<BOOST_PP_COUNTER>{typedef TYPE_PARAM type;};
			#ifdef ENUM_NAME_AUTOGEN
				ENUM_NAME_AUTOGEN(TYPE_PARAM, BOOST_PP_COUNTER)
			#endif
			#undef TYPE_PARAM
		#else
			#error use semiauto regtype error!
		#endif
	#endif
#endif