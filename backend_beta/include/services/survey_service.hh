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
    bool respond_survey(uint32_t response, uint32_t result);
};

#endif // survey_SERVICE_HPP
