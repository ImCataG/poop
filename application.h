//
// Created by catag on 6/2/2022.
//

#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H


#include <vector>
#include <memory>
#include "autoFarmer.h"
#include "boost.h"
#include "profileMinimal.h"

// singleton // game instance

class application {
private:
    application() = default;
    std::vector<boost> boostList;
    std::vector<autoFarmer> farmList;
    std::shared_ptr<profileMinimal> currentProfile;
    std::vector<std::shared_ptr<profileMinimal>> profileList;
    std::vector<boost> initboost();
    std::vector<autoFarmer> initfarmer();
    std::vector<std::shared_ptr<profileMinimal>> initplayerlist();
    void setBoostList(const std::vector<boost>& boostList_ );
    void setFarmList(const std::vector<autoFarmer>& farmList_);
    void setProfileList(const std::vector<std::shared_ptr<profileMinimal>>& profileList);

    std::vector<std::shared_ptr<profileMinimal>> readHardcorePlayers();
    std::vector<std::shared_ptr<profileMinimal>> readBasicPlayers();
public:
    application(const application&) = delete;
    application& operator=(const application&) = delete;
    static application& get_app();

    void init();

    void setCurrentProfile(std::shared_ptr<profileMinimal> currentProfile);

    //std::vector<std::string> getVectorOfProfileNames();

    //[[nodiscard]] const std::vector<boost> &getBoostList() const;
    //[[nodiscard]] const std::vector<autoFarmer> &getFarmList() const;
    [[nodiscard]] const std::vector<std::shared_ptr<profileMinimal>> &getProfileList() const;
    [[nodiscard]] const std::shared_ptr<profileMinimal> &getCurrentProfile() const;

    void addToProfileList(std::shared_ptr<profileMinimal> profile);

    void quitGame();
    void playCycle();
    void buyCycle();



};



#endif //OOP_APPLICATION_H
