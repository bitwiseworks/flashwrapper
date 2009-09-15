struct JRIEnvInterface {
        void*   reserved0;
        void*   reserved1;
        void*   reserved2;
        void*   reserved3;
        struct java_lang_Class* (JRICALL *FindClass)
        (JRIEnv* env, jint op, const char* a);
        void    (JRICALL *Throw)
        (JRIEnv* env, jint op, struct java_lang_Throwable* a);
        void    (JRICALL *ThrowNew)
        (JRIEnv* env, jint op, struct java_lang_Class* a, const char* b);
        struct java_lang_Throwable*     (JRICALL *ExceptionOccurred)
        (JRIEnv* env, jint op);
        void    (JRICALL *ExceptionDescribe)
        (JRIEnv* env, jint op);
        void    (JRICALL *ExceptionClear)
        (JRIEnv* env, jint op);
        jglobal (JRICALL *NewGlobalRef)
        (JRIEnv* env, jint op, void* a);
        void    (JRICALL *DisposeGlobalRef)
        (JRIEnv* env, jint op, jglobal a);
        void*   (JRICALL *GetGlobalRef)
        (JRIEnv* env, jint op, jglobal a);
        void    (JRICALL *SetGlobalRef)
        (JRIEnv* env, jint op, jglobal a, void* b);
        jbool   (JRICALL *IsSameObject)
        (JRIEnv* env, jint op, void* a, void* b);
        void*   (JRICALL *NewObject)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        void*   (JRICALL *NewObjectV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        void*   (JRICALL *NewObjectA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        struct java_lang_Class* (JRICALL *GetObjectClass)
        (JRIEnv* env, jint op, void* a);
        jbool   (JRICALL *IsInstanceOf)
        (JRIEnv* env, jint op, void* a, struct java_lang_Class* b);
        jint    (JRICALL *GetMethodID)
        (JRIEnv* env, jint op, struct java_lang_Class* a, const char* b, const char* c);
        void*   (JRICALL *CallMethod)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        void*   (JRICALL *CallMethodV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        void*   (JRICALL *CallMethodA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jbool   (JRICALL *CallMethodBoolean)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jbool   (JRICALL *CallMethodBooleanV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jbool   (JRICALL *CallMethodBooleanA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jbyte   (JRICALL *CallMethodByte)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jbyte   (JRICALL *CallMethodByteV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jbyte   (JRICALL *CallMethodByteA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jchar   (JRICALL *CallMethodChar)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jchar   (JRICALL *CallMethodCharV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jchar   (JRICALL *CallMethodCharA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jshort  (JRICALL *CallMethodShort)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jshort  (JRICALL *CallMethodShortV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jshort  (JRICALL *CallMethodShortA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jint    (JRICALL *CallMethodInt)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jint    (JRICALL *CallMethodIntV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jint    (JRICALL *CallMethodIntA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jlong   (JRICALL *CallMethodLong)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jlong   (JRICALL *CallMethodLongV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jlong   (JRICALL *CallMethodLongA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jfloat  (JRICALL *CallMethodFloat)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jfloat  (JRICALL *CallMethodFloatV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jfloat  (JRICALL *CallMethodFloatA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jdouble (JRICALL *CallMethodDouble)
        (JRIEnv* env, jint op, void* a, jint b, ...);
        jdouble (JRICALL *CallMethodDoubleV)
        (JRIEnv* env, jint op, void* a, jint b, va_list c);
        jdouble (JRICALL *CallMethodDoubleA)
        (JRIEnv* env, jint op, void* a, jint b, JRIValue* c);
        jint    (JRICALL *GetFieldID)
        (JRIEnv* env, jint op, struct java_lang_Class* a, const char* b, const char* c);
        void*   (JRICALL *GetField)
        (JRIEnv* env, jint op, void* a, jint b);
        jbool   (JRICALL *GetFieldBoolean)
        (JRIEnv* env, jint op, void* a, jint b);
        jbyte   (JRICALL *GetFieldByte)
        (JRIEnv* env, jint op, void* a, jint b);
        jchar   (JRICALL *GetFieldChar)
        (JRIEnv* env, jint op, void* a, jint b);
        jshort  (JRICALL *GetFieldShort)
        (JRIEnv* env, jint op, void* a, jint b);
        jint    (JRICALL *GetFieldInt)
        (JRIEnv* env, jint op, void* a, jint b);
        jlong   (JRICALL *GetFieldLong)
        (JRIEnv* env, jint op, void* a, jint b);
        jfloat  (JRICALL *GetFieldFloat)
        (JRIEnv* env, jint op, void* a, jint b);
        jdouble (JRICALL *GetFieldDouble)
        (JRIEnv* env, jint op, void* a, jint b);
        void    (JRICALL *SetField)
        (JRIEnv* env, jint op, void* a, jint b, void* c);
        void    (JRICALL *SetFieldBoolean)
        (JRIEnv* env, jint op, void* a, jint b, jbool c);
        void    (JRICALL *SetFieldByte)
        (JRIEnv* env, jint op, void* a, jint b, jbyte c);
        void    (JRICALL *SetFieldChar)
        (JRIEnv* env, jint op, void* a, jint b, jchar c);
        void    (JRICALL *SetFieldShort)
        (JRIEnv* env, jint op, void* a, jint b, jshort c);
        void    (JRICALL *SetFieldInt)
        (JRIEnv* env, jint op, void* a, jint b, jint c);
        void    (JRICALL *SetFieldLong)
        (JRIEnv* env, jint op, void* a, jint b, jlong c);
        void    (JRICALL *SetFieldFloat)
        (JRIEnv* env, jint op, void* a, jint b, jfloat c);
        void    (JRICALL *SetFieldDouble)
        (JRIEnv* env, jint op, void* a, jint b, jdouble c);
        jbool   (JRICALL *IsSubclassOf)
        (JRIEnv* env, jint op, struct java_lang_Class* a, struct java_lang_Class* b);
        jint    (JRICALL *GetStaticMethodID)
        (JRIEnv* env, jint op, struct java_lang_Class* a, const char* b, const char* c);
        void*   (JRICALL *CallStaticMethod)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        void*   (JRICALL *CallStaticMethodV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        void*   (JRICALL *CallStaticMethodA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jbool   (JRICALL *CallStaticMethodBoolean)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jbool   (JRICALL *CallStaticMethodBooleanV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jbool   (JRICALL *CallStaticMethodBooleanA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jbyte   (JRICALL *CallStaticMethodByte)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jbyte   (JRICALL *CallStaticMethodByteV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jbyte   (JRICALL *CallStaticMethodByteA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jchar   (JRICALL *CallStaticMethodChar)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jchar   (JRICALL *CallStaticMethodCharV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jchar   (JRICALL *CallStaticMethodCharA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jshort  (JRICALL *CallStaticMethodShort)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jshort  (JRICALL *CallStaticMethodShortV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jshort  (JRICALL *CallStaticMethodShortA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jint    (JRICALL *CallStaticMethodInt)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jint    (JRICALL *CallStaticMethodIntV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jint    (JRICALL *CallStaticMethodIntA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jlong   (JRICALL *CallStaticMethodLong)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jlong   (JRICALL *CallStaticMethodLongV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jlong   (JRICALL *CallStaticMethodLongA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jfloat  (JRICALL *CallStaticMethodFloat)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jfloat  (JRICALL *CallStaticMethodFloatV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jfloat  (JRICALL *CallStaticMethodFloatA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jdouble (JRICALL *CallStaticMethodDouble)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, ...);
        jdouble (JRICALL *CallStaticMethodDoubleV)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, va_list c);
        jdouble (JRICALL *CallStaticMethodDoubleA)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, JRIValue* c);
        jint    (JRICALL *GetStaticFieldID)
        (JRIEnv* env, jint op, struct java_lang_Class* a, const char* b, const char* c);
        void*   (JRICALL *GetStaticField)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jbool   (JRICALL *GetStaticFieldBoolean)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jbyte   (JRICALL *GetStaticFieldByte)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jchar   (JRICALL *GetStaticFieldChar)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jshort  (JRICALL *GetStaticFieldShort)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jint    (JRICALL *GetStaticFieldInt)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jlong   (JRICALL *GetStaticFieldLong)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jfloat  (JRICALL *GetStaticFieldFloat)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        jdouble (JRICALL *GetStaticFieldDouble)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b);
        void    (JRICALL *SetStaticField)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, void* c);
        void    (JRICALL *SetStaticFieldBoolean)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jbool c);
        void    (JRICALL *SetStaticFieldByte)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jbyte c);
        void    (JRICALL *SetStaticFieldChar)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jchar c);
        void    (JRICALL *SetStaticFieldShort)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jshort c);
        void    (JRICALL *SetStaticFieldInt)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jint c);
        void    (JRICALL *SetStaticFieldLong)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jlong c);
        void    (JRICALL *SetStaticFieldFloat)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jfloat c);
        void    (JRICALL *SetStaticFieldDouble)
        (JRIEnv* env, jint op, struct java_lang_Class* a, jint b, jdouble c);
        struct java_lang_String*        (JRICALL *NewString)
        (JRIEnv* env, jint op, const jchar* a, jint b);
        jint    (JRICALL *GetStringLength)
        (JRIEnv* env, jint op, struct java_lang_String* a);
        const jchar*    (JRICALL *GetStringChars)
        (JRIEnv* env, jint op, struct java_lang_String* a);
        struct java_lang_String*        (JRICALL *NewStringUTF)
        (JRIEnv* env, jint op, const jbyte* a, jint b);
        jint    (JRICALL *GetStringUTFLength)
        (JRIEnv* env, jint op, struct java_lang_String* a);
        const jbyte*    (JRICALL *GetStringUTFChars)
        (JRIEnv* env, jint op, struct java_lang_String* a);
        void*   (JRICALL *NewScalarArray)
        (JRIEnv* env, jint op, jint a, const char* b, const jbyte* c);
        jint    (JRICALL *GetScalarArrayLength)
        (JRIEnv* env, jint op, void* a);
        jbyte*  (JRICALL *GetScalarArrayElements)
        (JRIEnv* env, jint op, void* a);
        void*   (JRICALL *NewObjectArray)
        (JRIEnv* env, jint op, jint a, struct java_lang_Class* b, void* c);
        jint    (JRICALL *GetObjectArrayLength)
        (JRIEnv* env, jint op, void* a);
        void*   (JRICALL *GetObjectArrayElement)
        (JRIEnv* env, jint op, void* a, jint b);
        void    (JRICALL *SetObjectArrayElement)
        (JRIEnv* env, jint op, void* a, jint b, void* c);
        void    (JRICALL *RegisterNatives)
        (JRIEnv* env, jint op, struct java_lang_Class* a, char** b, void** c);
        void    (JRICALL *UnregisterNatives)
        (JRIEnv* env, jint op, struct java_lang_Class* a);
        struct java_lang_Class* (JRICALL *DefineClass)
        (JRIEnv* env, jint op, struct java_lang_ClassLoader* a, jbyte* b, jsize bLen);
        struct java_lang_String*        (JRICALL *NewStringPlatform)
        (JRIEnv* env, jint op, const jbyte* a, jint b, const jbyte* c, jint d);
        const jbyte*    (JRICALL *GetStringPlatformChars)
        (JRIEnv* env, jint op, struct java_lang_String* a, const jbyte* b, jint c);
};

