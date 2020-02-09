
int getTargetPercentage(int type) {
    float percent;
    switch (type) {
        case STOPWATCH:
            percent = elapsedTime * 100 / (cycler.target.finishTime * 3600);
            break;
        case DISTANCE:
            percent = totalDistance * 100 / cycler.target.distance;
            break;
        case ELEVATION:
            percent = totalElevation * 100 / cycler.target.elevation;
            break;
        default:
            percent = 0;
    }

    return int(percent);
}