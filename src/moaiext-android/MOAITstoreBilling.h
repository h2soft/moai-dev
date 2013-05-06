#ifndef	MOAITSTOREBILLING_H
#define	MOAITSTOREBILLING_H
      
#ifndef DISABLE_TSTORE

#include <moaicore/moaicore.h>

//================================================================//
// MOAITstoreBilling
//================================================================//
class MOAITstoreBilling :
	public MOAIGlobalClass < MOAITstoreBilling, MOAILuaObject > {
private:

	MOAILuaRef	mDialogCallback;
	
	//----------------------------------------------------------------//
	static int	_setApplicationId	( lua_State* L );
	static int	_requestPurchase	( lua_State* L );
	static int	_setListener 	( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAITstoreBilling );
		
	enum {
		PURCHASE_COMPLETE,
		PURCHASE_CANCEL,
		PURCHASE_ERROR,
		TOTAL,
	};
	
	MOAILuaRef		mListeners [ TOTAL ];
	
			MOAITstoreBilling		();
			~MOAITstoreBilling		();

	void 	NotifyPurchaseComplete ( );
	void 	NotifyPurchaseCancel ( );
	void 	NotifyPurchaseError ( int errorCode, int subErrorCode );
	void	RegisterLuaClass		( MOAILuaState& state );
};

#endif //DISABLE_TSTORE
#endif //MOAITSTOREBILLING_H
