/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/threads/nsIThreadPool.idl
 */

#ifndef __gen_nsIThreadPool_h__
#define __gen_nsIThreadPool_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "prthread.h"
#define NS_THREADPOOL_CID                            \
{ /* CC530631-7808-11d3-A181-0050041CAF44 */         \
    0xcc530631,                                      \
    0x7808,                                          \
    0x11d3,                                          \
    {0xa1, 0x81, 0x00, 0x50, 0x04, 0x1c, 0xaf, 0x44} \
}
#define NS_THREADPOOL_CONTRACTID "@mozilla.org/thread-pool;1"
#define NS_THREADPOOL_CLASSNAME "Thread Pool"
#if 0
typedef PRUint32 PRThreadPriority;

typedef PRUint32 PRThreadScope;

#endif
class nsIRunnable; /* forward declaration */


/* starting interface:    nsIThreadPool */
#define NS_ITHREADPOOL_IID_STR "0c728db0-6887-11d3-9382-00104ba0fd40"

#define NS_ITHREADPOOL_IID \
  {0x0c728db0, 0x6887, 0x11d3, \
    { 0x93, 0x82, 0x00, 0x10, 0x4b, 0xa0, 0xfd, 0x40 }}

class NS_NO_VTABLE nsIThreadPool : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ITHREADPOOL_IID)

  /* void DispatchRequest (in nsIRunnable runnable); */
  NS_IMETHOD DispatchRequest(nsIRunnable *runnable) = 0;

  /* void ProcessPendingRequests (); */
  NS_IMETHOD ProcessPendingRequests(void) = 0;

  /* void Shutdown (); */
  NS_IMETHOD Shutdown(void) = 0;

  /* void Init (in unsigned long aPoolMinThreadCount, in unsigned long aPoolMaxThreadCount, in unsigned long aThreadStackSize, in PRThreadPriority aThreadPriority, in PRThreadScope aThreadScope); */
  NS_IMETHOD Init(PRUint32 aPoolMinThreadCount, PRUint32 aPoolMaxThreadCount, PRUint32 aThreadStackSize, PRThreadPriority aThreadPriority, PRThreadScope aThreadScope) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSITHREADPOOL \
  NS_IMETHOD DispatchRequest(nsIRunnable *runnable); \
  NS_IMETHOD ProcessPendingRequests(void); \
  NS_IMETHOD Shutdown(void); \
  NS_IMETHOD Init(PRUint32 aPoolMinThreadCount, PRUint32 aPoolMaxThreadCount, PRUint32 aThreadStackSize, PRThreadPriority aThreadPriority, PRThreadScope aThreadScope); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSITHREADPOOL(_to) \
  NS_IMETHOD DispatchRequest(nsIRunnable *runnable) { return _to DispatchRequest(runnable); } \
  NS_IMETHOD ProcessPendingRequests(void) { return _to ProcessPendingRequests(); } \
  NS_IMETHOD Shutdown(void) { return _to Shutdown(); } \
  NS_IMETHOD Init(PRUint32 aPoolMinThreadCount, PRUint32 aPoolMaxThreadCount, PRUint32 aThreadStackSize, PRThreadPriority aThreadPriority, PRThreadScope aThreadScope) { return _to Init(aPoolMinThreadCount, aPoolMaxThreadCount, aThreadStackSize, aThreadPriority, aThreadScope); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSITHREADPOOL(_to) \
  NS_IMETHOD DispatchRequest(nsIRunnable *runnable) { return !_to ? NS_ERROR_NULL_POINTER : _to->DispatchRequest(runnable); } \
  NS_IMETHOD ProcessPendingRequests(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ProcessPendingRequests(); } \
  NS_IMETHOD Shutdown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Shutdown(); } \
  NS_IMETHOD Init(PRUint32 aPoolMinThreadCount, PRUint32 aPoolMaxThreadCount, PRUint32 aThreadStackSize, PRThreadPriority aThreadPriority, PRThreadScope aThreadScope) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aPoolMinThreadCount, aPoolMaxThreadCount, aThreadStackSize, aThreadPriority, aThreadScope); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsThreadPool : public nsIThreadPool
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITHREADPOOL

  nsThreadPool();
  virtual ~nsThreadPool();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsThreadPool, nsIThreadPool)

nsThreadPool::nsThreadPool()
{
  /* member initializers and constructor code */
}

nsThreadPool::~nsThreadPool()
{
  /* destructor code */
}

/* void DispatchRequest (in nsIRunnable runnable); */
NS_IMETHODIMP nsThreadPool::DispatchRequest(nsIRunnable *runnable)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ProcessPendingRequests (); */
NS_IMETHODIMP nsThreadPool::ProcessPendingRequests()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Shutdown (); */
NS_IMETHODIMP nsThreadPool::Shutdown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Init (in unsigned long aPoolMinThreadCount, in unsigned long aPoolMaxThreadCount, in unsigned long aThreadStackSize, in PRThreadPriority aThreadPriority, in PRThreadScope aThreadScope); */
NS_IMETHODIMP nsThreadPool::Init(PRUint32 aPoolMinThreadCount, PRUint32 aPoolMaxThreadCount, PRUint32 aThreadStackSize, PRThreadPriority aThreadPriority, PRThreadScope aThreadScope)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

extern NS_COM nsresult
NS_NewThreadPool(nsIThreadPool* *result,
                 PRUint32 minThreads, PRUint32 maxThreads,
                 PRUint32 stackSize = 0,
                 PRThreadPriority priority = PR_PRIORITY_NORMAL,
                 PRThreadScope scope = PR_GLOBAL_THREAD);

#endif /* __gen_nsIThreadPool_h__ */
