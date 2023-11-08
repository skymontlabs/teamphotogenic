enum class MessageType : int
{
    // User authentication and management
    CreateUser = 1,
    UpdateUser = 2,
    DeleteUser = 3,
    GetUser = 4,
    LoginUser = 5,

    // User session management
    UserSessionStart = 10,
    UserImageSessionStart = 11,
    UserSessionRenew = 11,
    UserSessionEnd = 12,

    // Image handling
    UploadImage = 20,
    UpdateImageDetails = 21,
    DeleteImage = 22,
    FetchImage = 23,
    ListUserImages = 24,

    // Rating and critique handling
    SubmitRating = 30,
    UpdateRating = 31,
    DeleteRating = 32,
    FetchRating = 33,
    ListImageRatings = 34,
    SubmitCritique = 35,
    UpdateCritique = 36,
    DeleteCritique = 37,
    FetchCritique = 38,
    ListImageCritiques = 39,

    // Elo scoring
    RecordPairwiseChoice = 40,
    UpdateEloScores = 41,

    // Experiment handling
    CreateExperiment = 50,
    UpdateExperiment = 51,
    DeleteExperiment = 52,
    GetExperimentDetails = 53,
    ListUserExperiments = 54,

    // Tag management
    AddTag = 60,
    RemoveTag = 61,
    ListTags = 62,

    // Admin and maintenance commands
    AdminAction = 70,
    MaintenanceMode = 71,

    // System health and metrics
    SystemHealthCheck = 80,
    FetchSystemMetrics = 81,

    // Notifications
    SendNotification = 90,
    FetchNotifications = 91,

    // Error and status messages
    ErrorMessage = 100,
    StatusUpdate = 101,

    // Keep-alive and connection management
    KeepAlive = 110,
    ConnectionTerminate = 111
};


User Management
UserRegister: Register a new user account.
UserLogin: Authenticate a user.
UserLogout: Log out a user.
UserProfileUpdate: Update user profile information.
UserPasswordChange: Change a user's password.
UserDeactivate: Deactivate a user account.
Session Management
SessionStart: Start a new user session.
SessionRenew: Renew an existing user session.
SessionEnd: End a user session.
Image Uploads and Management
ImageUploadStart: Begin the process of uploading an image.
ImageUploadChunk: Upload a part of the image if chunking is needed.
ImageUploadComplete: Complete the image upload process.
ImageDelete: Delete an uploaded image.
ImageUpdateMetadata: Update image metadata, like tags or description.
ImageFetchList: Retrieve a list of images, possibly with pagination.
Rating and Reviews
ImageRate: Rate an image.
ImageFetchRatings: Get ratings for an image.
ExperimentCreate: Start a new rating experiment.
ExperimentFetchResults: Fetch the results of a rating experiment.
RatingEloUpdate: Update the Elo rating after a pairwise comparison.
RatingSubmitLikert: Submit a Likert scale rating for an image.
RatingPairwiseVote: Submit a vote in a pairwise image comparison.
Comments and Interactions
CommentPost: Post a comment on an image.
CommentFetch: Fetch comments for an image.
CommentDelete: Delete a comment.
UserFollow: Follow another user.
UserUnfollow: Unfollow a user.
UserFetchFollowers: Retrieve the list of followers for a user.
UserFetchFollowing: Retrieve the list of users a user is following.
Notifications
NotificationSubscribe: Subscribe to notifications.
NotificationUnsubscribe: Unsubscribe from notifications.
NotificationFetch: Fetch notifications for the user.
Search and Discovery
SearchImages: Search for images by tags, ratings, etc.
DiscoverTrending: Discover trending images or experiments.
UserRecommendations: Get user recommendations (if you implement a suggestion feature).
Miscellaneous
Heartbeat: A simple message to ensure the WebSocket connection is alive.
ErrorReport: Report an error from the client side.
UserActivityLog: Log user activity for analytics purposes.
Real-Time Updates (Event Pushes from Server)
RatingUpdateNotify: Notify users of updates in ratings.
CommentNotify: Notify users of new comments.
ExperimentUpdateNotify: Notify users of changes in an experiment status.
UserNotificationPush: Push notifications to the user for any updates.


