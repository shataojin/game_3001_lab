#pragma once
#ifndef __TILE__
#define __TILE__

#include <string>
#include "Label.h"
#include "NavigationObject.h"
#include "TileType.h"
#include "TileStatus.h"
#include "TileNeighbour.h"

class Tile : public NavigationObject
{
public:
	Tile(SDL_FRect dst = { 0,0,0,0 }, TileType type = TileType::PASSABLE);
	~Tile() override;

	// DisplayObject Life-Cycle Functions
	void Draw() override;
	void DrawNavigation(); // Not from GameObject.
	void Update() override;
	void Clean() override;

	// Getters and Setters
	[[nodiscard]] TileType GetTileType() const;
	void SetTileType(TileType type);
	[[nodiscard]] TileStatus GetTileStatus() const;
	void SetTileStatus(TileStatus status);
	[[nodiscard]] Tile* GetTileNeighbour(TileNeighbour position);
	void SetTileNeighbour(TileNeighbour position, Tile* tile);
	[[nodiscard]] unsigned short GetTileHealth() const;
	void SetTileHealth(int health);
	[[nodiscard]] float GetTileCost() const;
	void SetTileCost(float cost);
	void SetDrawData(SDL_Rect src, const std::string& textureKey);
	[[nodiscard]] SDL_Rect GetSrc() const;
	[[nodiscard]] const std::string& GetTextureKey() const;

	// Others
	void AddLabels();
	[[nodiscard]] bool GetLabelsEnabled() const;
	void SetLabelsEnabled(bool state);
	[[nodiscard]] Tile* Clone() const;
	void SetPos(float col, float row, float sizeX, float sizeY);
private:
	std::string m_textureKey;
	SDL_Rect m_src;
	SDL_FRect m_dst;

	TileType m_type;
	TileStatus m_status;
	unsigned short m_health; // TODO: Add destructible functionality.
	float m_cost;

	Label* m_costLabel;
	Label* m_statusLabel;
	bool m_labelsEnabled;

	Tile* m_neighbours[static_cast<unsigned>(TileNeighbour::NUM_OF_NEIGHBOUR_TILES)];
};

#endif /* defined (__TILE__) */