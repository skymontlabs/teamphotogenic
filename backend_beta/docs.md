### Core Application Files
- `main.cpp`: The entry point of the application where the main server loop is initiated.

### Server Setup
- `AppServer.hpp/cpp`: Defines the server class that sets up, configures, and runs the Boost ASIO server.

### Session Management
- `Session.hpp/cpp`: Manages user sessions, handling the lifetime and interactions of each connected user.

### Message Routing
- `MessageRouter.hpp/cpp`: Routes incoming messages to the correct handlers based on the message type.

### User Management
- `UserModel.hpp/cpp`: Represents the user entity and handles operations such as creation, authentication, and profile management.

### Image Management
- `ImageModel.hpp/cpp`: Represents the image entity and handles operations such as uploading, storing, and retrieving images.

### Rating Management
- `RatingModel.hpp/cpp`: Manages the ratings for images, including calculating scores and storing user feedback.

### Database Connectivity
- `DatabaseConnector.hpp/cpp`: Provides an interface for connecting to and interacting with the Cassandra database.

### Cache Connectivity
- `RedisConnector.hpp/cpp`: Handles the connection to the Redis cache and performs cache-related operations.

### Utility and Helpers
- `Utils.hpp/cpp`: Contains utility functions and common code that is used across various parts of the application.
- `Constants.hpp`: Defines constants used throughout the application.
- `ErrorHandler.hpp/cpp`: Manages error handling and reporting for the application.

### Enums and Type Definitions
- `Types.hpp`: Contains enum definitions and type aliases used across the application.

### Protocol Definitions
- `Protocol.hpp`: Defines the protocol used for communication, including message format and types.

### WebSocket Communication
- `WebSocketSession.hpp/cpp`: Manages a single WebSocket connection, handling sending and receiving messages.
- `WebSocketManager.hpp/cpp`: Manages all WebSocket sessions, providing a way to broadcast and control active connections.

### Asynchronous Task Management
- `TaskQueue.hpp`: Defines a thread-safe task queue for scheduling tasks to run asynchronously.
- `ThreadPool.hpp/cpp`: Implements a pool of threads that can run tasks concurrently, managing their execution and lifecycle.

### Configuration
- `Config.hpp/cpp`: Handles loading and accessing configuration settings for the application.

### Logging
- `Logger.hpp/cpp`: Provides a logging interface for the application, which can be used for debugging and audit trails.
