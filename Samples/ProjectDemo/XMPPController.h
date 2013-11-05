#import <Foundation/Foundation.h>
#import "XMPPFramework.h"
#import "Document.h"

@interface XMPPController : NSObject
{
	XMPPStream *xmppStream;
	XMPPRosterMemoryStorage *xmppRosterStorage;
	XMPPRoster *xmppRoster;
	
	Document *currentDocument;
	
	NSMutableDictionary *sharingSessionsByPersistentRootUUID;
}

+ (XMPPController *) sharedInstance;

- (void) reconnect;
- (void) shareWithInspectorForDocument: (Document*)doc;

@end