#import <UIKit/UIKit.h>

typedef void (^actionHandler)(void);
typedef NS_ENUM(NSUInteger, AAPullToRefreshState) {
    AAPullToRefreshStateNormal = 0,
    AAPullToRefreshStateStopped,
    AAPullToRefreshStateLoading,
};
typedef NS_ENUM(NSUInteger, AAPullToRefreshPosition) {
    AAPullToRefreshPositionTop,
    AAPullToRefreshPositionBottom,
    AAPullToRefreshPositionLeft,
    AAPullToRefreshPositionRight,
};

@interface AAPullToRefresh : UIView

@property (nonatomic, assign) CGFloat originalInsetTop;
@property (nonatomic, assign) CGFloat originalInsetBottom;
@property (nonatomic, assign, readonly) AAPullToRefreshPosition position;
@property (nonatomic, strong) UIScrollView *scrollView;
@property (nonatomic, copy) void (^pullToRefreshHandler)(AAPullToRefresh *v);

// user customizable.
@property (nonatomic, assign) BOOL showPullToRefresh;
@property (nonatomic, assign) CGFloat threshold;
@property (nonatomic, strong) UIImage *imageIcon;
@property (nonatomic, strong) UIColor *borderColor;
@property (nonatomic, assign) CGFloat borderWidth;

- (id)initWithImage:(UIImage *)image position:(AAPullToRefreshPosition)position;
- (void)stopIndicatorAnimation;
- (void)manuallyTriggered;
- (void)setSize:(CGSize)size;

- (void)removeSelf;

@end

@interface UIScrollView (AAPullToRefresh)
- (AAPullToRefresh *)addPullToRefreshPosition:(AAPullToRefreshPosition)position actionHandler:(void (^)(AAPullToRefresh *v))handler;
@end
