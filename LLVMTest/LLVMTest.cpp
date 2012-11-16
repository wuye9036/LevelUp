// LLVMTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "llvm/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/IRBuilder.h"
#include <llvm/Support/StandardPasses.h>

#include <vector>

using namespace llvm;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	LLVMContext ctxt;

	Module* mod = new Module("Test Module", ctxt);

	const Type* int32_type = cast<Type>( Type::getInt32Ty(ctxt) );
	
	vector<const Type*> param_types;
	param_types.push_back(int32_type);
	param_types.push_back(int32_type);

	FunctionType* fn_type = FunctionType::get( int32_type, param_types, false );
	Function* fn = Function::Create( fn_type, Function::ExternalLinkage, "foo", mod );

	size_t arg_idx = 0;
	Argument* arg_v0 = &(*(fn->getArgumentList().begin()));
	Argument* arg_v1 = fn->getArgumentList().begin()->getNextNode();

	arg_v0->setName("v0");
	arg_v1->setName("v1");

	IRBuilder<> builder(ctxt);
	BasicBlock* entry_block = BasicBlock::Create(ctxt, "entry", fn);
	
	BasicBlock* yes_block = BasicBlock::Create( ctxt, "yes", fn );
	builder.SetInsertPoint(yes_block);
	builder.CreateRet( arg_v0 );
	BasicBlock* banner_block = BasicBlock::Create( ctxt, "", fn );
	builder.SetInsertPoint(banner_block);
	BasicBlock* after_yes_block = banner_block;

	BasicBlock* no_block = BasicBlock::Create( ctxt, "no", fn );
	builder.SetInsertPoint(no_block);
	builder.CreateRet( arg_v1 );
	banner_block = BasicBlock::Create( ctxt, "", fn );
	builder.SetInsertPoint(banner_block);
	BasicBlock* after_no_block = banner_block;

	builder.SetInsertPoint(entry_block);
	Value* cmp = builder.CreateICmpSLT( arg_v0, arg_v1, "cmp" );
	builder.CreateCondBr( cmp, yes_block, no_block );

	BasicBlock* aggregated = BasicBlock::Create( ctxt, "aggregated", fn );

	builder.SetInsertPoint(after_yes_block);
	builder.CreateBr(aggregated);

	builder.SetInsertPoint(after_no_block);
	builder.CreateBr(aggregated);

	builder.SetInsertPoint(aggregated);
	builder.CreateRet( ConstantInt::get( int32_type, 0, true ) );

	mod->dump();

	FunctionPassManager fpm(mod);
	createStandardFunctionPasses(&fpm, 1);	

	fpm.doInitialization();

	fpm.run( *fn );

	printf("\r\n==========================================================\r\n");
	printf("Optimized:\r\n");

	mod->dump();

	system("pause");
	return 0;
}

