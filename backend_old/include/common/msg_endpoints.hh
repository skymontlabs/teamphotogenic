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

    // Elo score (pairing)
    SubmitElo = 45,
    UpdateElo = 46,
    DeleteElo = 47,
    FetchElo = 48,
    ListImageElos = 49,

    // Experiment handling
    CreateExperiment = 50,
    ReadExperiment = 51,
    ReadExperimentNoMetadata = 51,
    ReadExperimentsByUser = 51,
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

enum class response_ode {
    OK = 1,
    CREATED_NO_BODY = 2,
    CREATED_WITH_BODY = 2,
    NOT_FOUND = 100,
}
