#pragma once

class SceneController;
struct ConfigOptions;

class GameStates
{
public:
	GameStates(SceneController* scene);

public:
	void StartGame();

	static void GetConfigOptions(ConfigOptions& opts);

private:
	void StartNovel();
	void GoToMainMenu();
	void GoToEscapeMenu();
	void ContinueNovel();

private:
	void NextStatement();
	SceneController* Scene = nullptr;

private:
	unsigned int frame = 0;
};

