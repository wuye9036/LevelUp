#ifndef TYPE_REGISTER_H
#define TYPE_REGISTER_H

	#define BEGIN_REGISTER_TYPE() "type_register.h"

#else
	#ifdef BEGIN_REGISTER_TYPE
		struct empty{};
		typedef int type_id;
		template<class T> struct type_encode{static const type_id id = 0; };
		template<int id> struct type_decode{typedef empty type;};

		#define INIT_SEMIAUTO_REGTYPE
		#define REGTYPE() "semiauto_regtype.h"
		#include REGTYPE()
		#define END_REGISTER_TYPE() "type_register.h"
		#undef BEGIN_REGISTER_TYPE
	#else
		#ifdef END_REGISTER_TYPE
			#define FIN_SEMIAUTO_REGTYPE
			#include REGTYPE()
			static const int _registered_types_count = BOOST_PP_COUNTER;
			#define BEGIN_REGISTER_TYPE() "type_register.h"
			#undef REGTYPE
			#undef END_REGISTER_TYPE
		#else
			#error check macro!
		#endif
	#endif
#endif