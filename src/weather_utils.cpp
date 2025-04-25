#include "weather_utils.h"
#include "weather_data.h"

String parseCondition(const String &conditionCode) {
    if (conditionCode == "clear")
        return "ясно";
    else if (conditionCode == "partly-cloudy")
        return "малооблачно";
    else if (conditionCode == "cloudy")
        return "облачно с прояснениями";
    else if (conditionCode == "overcast")
        return "пасмурно";
    else if (conditionCode == "light-rain")
        return "небольшой дождь";
    else if (conditionCode == "rain")
        return "дождь";
    else if (conditionCode == "heavy-rain")
        return "сильный дождь";
    else if (conditionCode == "showers")
        return "ливень";
    else if (conditionCode == "wet-snow")
        return "дождь со снегом";
    else if (conditionCode == "light-snow")
        return "небольшой снег";
    else if (conditionCode == "snow")
        return "снег";
    else if (conditionCode == "snow-showers")
        return "снегопад";
    else if (conditionCode == "hail")
        return "град";
    else if (conditionCode == "thunderstorm")
        return "гроза";
    else if (conditionCode == "thunderstorm-with-rain")
        return "дождь с грозой";
    else if (conditionCode == "thunderstorm-with-hail")
        return "гроза с градом";

    return "неизвестно";
}

String parseWindDirection(const String &windDirCode) {
    if (windDirCode == "nw")
        return "северо-западный";
    else if (windDirCode == "n")
        return "северный";
    else if (windDirCode == "ne")
        return "северо-восточный";
    else if (windDirCode == "e")
        return "восточный";
    else if (windDirCode == "se")
        return "юго-восточный";
    else if (windDirCode == "s")
        return "южный";
    else if (windDirCode == "sw")
        return "юго-западный";
    else if (windDirCode == "w")
        return "западный";
    else if (windDirCode == "c")
        return "штиль";

    return "неизвестно";
}

String parseCloudness(float value) {
    Cloudness cloudness;

    if (value == 0.0f) {
        cloudness = Cloudness::Clear;
    } else if (value == 0.25f) {
        cloudness = Cloudness::FewClouds;
    } else if (value == 0.5f) {
        cloudness = Cloudness::PartlyCloudy;
    } else if (value == 0.75f) {
        cloudness = Cloudness::MostlyCloudy;
    } else {
        cloudness = Cloudness::Overcast;
    }

    switch (cloudness) {
    case Cloudness::Clear:
        return "ясно";
    case Cloudness::FewClouds:
        return "малооблачно";
    case Cloudness::PartlyCloudy:
        return "облачно с прояснениями";
    case Cloudness::MostlyCloudy:
        return "облачно с прояснениями";
    case Cloudness::Overcast:
        return "пасмурно";
    default:
        return "неизвестно";
    }
}