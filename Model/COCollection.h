/**
    Copyright (C) 2011 Quentin Mathe

    Date:  December 2011
    License:  MIT  (see COPYING)
 */

#import <Foundation/Foundation.h>
#import <EtoileFoundation/EtoileFoundation.h>
#import <CoreObject/COObject.h>

/**
 * @group Object Collection and Organization
 * @abstract COCollection is a abstract class that provides a common API to 
 * various concrete collection subclasses such as COGroup or COContainer.
 *
 * COCollection represents a mutable collection, but subclasses can be immutable.
 *
 * The collection content is stored in the property returned by -contentKey. 
 * If the content property is not 'objects', -contentKey must be overriden.
 *
 * COCollection adopts the collection protocols. Which means you can mutate 
 * COCollection subclass instances using ETCollectionMutation methods such 
 * as -addObject:, -insertObject:atIndex:, -removeObject:atIndex:, -removeObject:
 * etc. In addition, the class provides -addObjects:.
 *
 * Every time the collection is mutated, COCollection posts a 
 * ETSourceDidUpdateNotification (in addition the usual Key-Value-Observing 
 * notifications).<br />
 * If you override ETCollectionMutation primitive methods in a COCollection 
 * subclass, you must call -didUpdate in the new implementation (to ensure 
 * ETSourceDidUpdateNotification is posted).
 */
@interface COCollection : COObject <ETCollection, ETCollectionMutation>


/** @taskunit Metamodel */


/**
 * Returns a multivalued, ordered and persistent property.
 *
 * You can use this method to easily describe your collection content in a way
 * that matches the superclass contraints.
 * 
 * The returned property can be customized, then inserted into the entity built 
 * with +newEntityDescription in your subclass.
 * 
 * Name and type must not be nil.
 *
 * Both type and opposite must be entity description names such as 
 * <em>Anonymous.NSObject</em> or <em>NSObject</em>.<br />
 * The <em>Anonymous</em> prefix is optional. Most entity description names 
 * don't require a prefix, because they don't belong to a package description 
 * but are just registered at runtime directly, and belong to this Anonymous 
 * package as a result.
 *
 * Can be overriden to change the constraints applying to the property.
 */
+ (ETPropertyDescription *)contentPropertyDescriptionWithName: (NSString *)aName
                                                         type: (NSString *)aType
                                                     opposite: (NSString *)oppositeType;
/**
 * <override-never />
 * Returns UTI type for the collection elements.
 *
 * For inserting a new object in the collection, you can use this method to 
 * know the object class to instantiate. 
 *
 * The returned UTI depends on -[ETPropertyDescription type] for the content 
 * property description (looked up using -contentKey).<br />
 * To customize the type, you must edit the receiver entity description.
 *
 * See also -[ETController currentObjectType] in EtoileUI.
 */
@property (nonatomic, readonly) ETUTI *objectType;
/**
 * <override-never />
 * Returns whether the collection is ordered.
 *
 * The returned value is controlled by -[ETPropertyDescription isOrdered] for 
 * the content property description (looked up using -contentKey).
 */
@property (nonatomic, readonly, getter=isOrdered) BOOL ordered;


/** @taskunit Content Access */


/**
 * <override-dummy />
 * Returns the property name that holds the collection content.
 *
 * This method is used by COCollection to implement ETCollection and
 * ETCollectionMutation protocol methods. Subclasses must thereby return a 
 * valid key, other the collection API won't behave correctly.
 *
 * For example, -[ETCollectionMutation insertObjects:atIndexes:hints:] 
 * implementation uses the content key to retrieve the content collection.
 *
 * By default, returns <em>objects</em>.
 */
@property (nonatomic, readonly) NSString *contentKey;


/** @taskunit Collection Mutation Additions */


/**
 * Adds all the given objects to the receiver content.
 */
- (void)addObjects: (NSArray *)anArray;
/**
 * Posts ETSourceDidUpdateNotification.
 *
 * You must invoke this method every time the collection is changed.
 * For example, when you override 
 * -[ETCollectionMutation insertObjects:atIndexes:hints:].
 *
 * EtoileUI relies on this notification to reload the UI transparently.
 */
- (void)didUpdate;


/** @taskunit Object Matching */


/**
 * Returns the first object whose identifier matches.
 *
 * The search is shallow, in other words limited to the objects in the receiver 
 * content.
 *
 * See -[COObject identifier].
 */
- (id)objectForIdentifier: (NSString *)anId;

@end


/** 
 * @group Object Collection and Organization 
 */
@interface COObject (COCollectionTypeQuerying)

/**
 * Returns whether the receiver is a group or not.
 */
@property (nonatomic, readonly) BOOL isGroup;
/**
 * Returns whether the receiver is a tag or not.
 *
 * A tag is group that belongs to -[COEditingContext tagGroup].
 */
@property (nonatomic, readonly) BOOL isTag;
/**
 * Returns whether the receiver is a container or not.
 */
@property (nonatomic, readonly) BOOL isContainer;
/**
 * Returns whether the receiver is a library or not.
 *
 * A library is a container.
 */
@property (nonatomic, readonly) BOOL isLibrary;
@end
