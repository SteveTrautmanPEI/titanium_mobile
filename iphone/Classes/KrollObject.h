/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2010 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
#import <Foundation/Foundation.h>
#import "TiCore.h"
#import "TiBase.h"

@class KrollContext, KrollCallback;
extern TiClassRef KrollObjectClassRef;

void KrollFinalizer(TiObjectRef ref);
void KrollInitializer(TiContextRef ctx, TiObjectRef object);
TiValueRef KrollGetProperty(TiContextRef jsContext, TiObjectRef obj, TiStringRef prop, TiValueRef* exception);
bool KrollSetProperty(TiContextRef jsContext, TiObjectRef obj, TiStringRef prop, TiValueRef value, TiValueRef* exception);
bool KrollDeleteProperty(TiContextRef ctx, TiObjectRef object, TiStringRef propertyName, TiValueRef* exception);

// this is simply a marker interface that we can use 
// to determine if a object is undefined
@interface KrollUndefined : NSObject
+(KrollUndefined*)undefined;
@end


//
// KrollObject is a generic native wrapper around a native object exposed as a JS object 
// in JS land. 
//

@class KrollBridge;
@interface KrollObject : NSObject {
@private
	NSMutableDictionary *properties;
	NSMutableDictionary *statics;
	TiObjectRef jsobject;
	TiObjectRef propsObject;
	BOOL targetable;
	BOOL finalized;
	BOOL protecting;
@protected
	id target;
	KrollContext *context;
	KrollBridge *bridge;	//Used only in finalizing for sake of safe lookup.
}
@property(nonatomic,assign) BOOL finalized;
@property(nonatomic,readonly) KrollBridge *bridge;

-(id)initWithTarget:(id)target_ context:(KrollContext*)context_;

+(TiValueRef)create:(id)object context:(KrollContext*)context_;
+(id)toID:(KrollContext*)context value:(TiValueRef)ref;
+(TiValueRef)toValue:(KrollContext*)context value:(id)obj;
+(id)nonNull:(id)value;


-(id)valueForKey:(NSString *)key;
-(void)deleteKey:(NSString *)key;
-(void)setValue:(id)value forKey:(NSString *)key;
-(void)setStaticValue:(id)value forKey:(NSString*)key purgable:(BOOL)purgable;
-(KrollContext*)context;
-(id)target;

@property(nonatomic,assign) TiObjectRef propsObject;
-(TiObjectRef)jsobject;
-(void)invalidateJsobject;

-(void)noteKeylessKrollObject:(KrollObject *)value;
-(void)forgetKeylessKrollObject:(KrollObject *)value;
-(void)protectJsobject;
-(void)unprotectJsobject;

-(void)noteKrollObject:(KrollObject *)value forKey:(NSString *)key;
-(void)noteObject:(TiObjectRef)storedJSObject forTiString:(TiStringRef) keyString context:(TiContextRef) jsxContext;
-(void)forgetObjectForTiString:(TiStringRef) keyString context:(TiContextRef) jsContext;


-(void)storeCallback:(KrollCallback *)eventCallback forEvent:(NSString *)eventName;
-(void)removeCallback:(KrollCallback *)eventCallback forEvent:(NSString *)eventName;
-(void)triggerEvent:(NSString *)eventName withObject:(NSDictionary *)eventData thisObject:(KrollObject *)thisObject;

@end

