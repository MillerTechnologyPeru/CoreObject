/**
    Copyright (C) 2013 Eric Wasylishen, Quentin Mathe

    Date:  January 2013
    License:  MIT  (see COPYING)
 */

#import <CoreObject/COEditingContext.h>

NS_ASSUME_NONNULL_BEGIN

/** 
 * @group Debugging
 * @abstract Additions to debug loaded objects and change tracking, accross 
 * all persistent roots and branches loaded in an editing context
 *
 * This category isn't part of the official public API. 
 */
@interface COEditingContext (CODebugging)


/** @taskunit Loaded Objects */


/**
 * Returns the objects presently managed by the receiver in memory.
 *
 * The returned objects include -insertedObjects.
 *
 * Faults can be included among the returned objects.
 *
 * See also -loadedObjectUUIDs.
 */
@property (nonatomic, readonly) NSArray<__kindof COObject *> *loadedObjects;
/**
 * Returns the root objects presently managed by the receiver in memory.
 *
 * Faults and inserted objects can be included among the returned objects.
 *
 * The returned objects are a subset of -loadedObjects.
 */
@property (nonatomic, readonly) NSArray<__kindof COObject *> *loadedRootObjects;


/** @taskunit Pending Changes */


/**
 * Returns the new objects added to the context with -insertObject: and to be
 * added to the store on the next commit.
 *
 * After a commit, returns an empty set.
 */
@property (nonatomic, readonly) NSArray<__kindof COObject *> *insertedObjects;
/**
 * Returns the objects whose properties have been edited in the context and to
 * be updated in the store on the next commit.
 *
 * After a commit, returns an empty set.
 */
@property (nonatomic, readonly) NSArray<__kindof COObject *> *updatedObjects;
/**
 * Returns the union of the inserted and updated objects. See -insertedObjects
 * and -updatedObjects.
 *
 * After a commit, returns an empty set.
 */
@property (nonatomic, readonly) NSArray<__kindof COObject *> *changedObjects;

@end

NS_ASSUME_NONNULL_END
