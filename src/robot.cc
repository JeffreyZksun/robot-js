#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> Say(const Arguments& args) {
	HandleScope scope;
	
	// Entry check
	if (args.Length() != 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
  
	Local<String> name= args[0]->ToString();
	Local<String> msg = String::Concat(String::New("hello "), name);
	Local<Function> cb = Local<Function>::Cast(args[1]);
  
	const unsigned argc = 1;
	Local<Value> argv[argc] = { Local<Value>::New(msg) };
	cb->Call(Context::GetCurrent()->Global(), argc, argv);
  
	return scope.Close(Undefined());  
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("say"),
      FunctionTemplate::New(Say)->GetFunction());
}

NODE_MODULE(robot, init)