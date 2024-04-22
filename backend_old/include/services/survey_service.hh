#ifndef survey_SERVICE_HPP
#define survey_SERVICE_HPP

#include "surveyDAO.hpp"
#include "survey.hpp"

class survey_service
{
    surveyDAO& surveyDAO;  // Reference to the Data Access Object for surveys

public:
    surveyService(surveyDAO& dao);

    // Service operations

    // Authenticate survey through login
    bool respond_survey(const uint8_t* in, user_data ud, response_callback wcb);
};

#endif // survey_SERVICE_HPP


bool survey_service::respond_survey(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint64_t question_id = READ64(in)
    uint64_t response_id = READ64(in)
    
}
