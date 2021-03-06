#include "TiledLevel.h"
#include "TextureManager.h"
#include <fstream>

TiledLevel::TiledLevel(const std::string& levelMap, const std::string& tileData, 
	const std::string& texturePath, const std::string& textureKey,
	const SDL_Point tileSrcSize, const SDL_FPoint tileDstSize, const unsigned short rows, const unsigned short cols, 
	const bool hasNavigation, const bool isRendered): m_hasNavigation(hasNavigation),
	m_renderTiles(isRendered), m_textureKey(textureKey), m_rows(rows), m_cols(cols)
{
	TextureManager::Instance().Load(texturePath, textureKey);
	// Create map of prototypes.
	std::ifstream inFile(tileData);
	if (inFile.is_open())
	{
		char key;
		int type;
		int x, y;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> type;
			m_tiles.emplace(key, new Tile({ 0.0f,0.0f, tileDstSize.x, tileDstSize.y }, 
				static_cast<TileType>(type)));
			m_tiles[key]->SetDrawData({ x * tileSrcSize.x, y * tileSrcSize.y,
				tileSrcSize.x, tileSrcSize.y }, textureKey);
		}
	}
	inFile.close();
	// Create level of Tiles.
	inFile.open(levelMap);
	if (inFile.is_open())
	{
		char key;
		m_level.reserve(m_rows * m_cols);
		for (unsigned short row = 0; row < rows; row++)
		{
			for (unsigned short col = 0; col < cols; col++)
			{
				inFile >> key;
				Tile* tile = m_tiles[key]->Clone(); // Clone only copies m_dst and m_type.
				tile->SetPos(col, row, tileDstSize.x, tileDstSize.y);
				// Some flag-based setting of optional data.
				if (m_renderTiles)
				{
					tile->SetDrawData(m_tiles[key]->GetSrc(), m_tiles[key]->GetTextureKey());
				}
				if (m_hasNavigation)
				{
					tile->SetGridPosition(col, row);
					tile->AddLabels();
				}
				m_level.push_back(tile);
				// Push into additional vectors for quick testing.
				if (tile->GetTileType() == TileType::IMPASSABLE)
					m_impassables.push_back(tile);
				if (tile->GetTileType() == TileType::HAZARD)
					m_hazards.push_back(tile);
				// TODO: Destructibles.
			}
		}
	}
	inFile.close();
	if (m_hasNavigation) LinkTiles();
}

TiledLevel::~TiledLevel()
{
	for (const auto tile : m_level)
	{
		delete tile;
	}
	m_level.clear();
	for (const auto& prototile : m_tiles)
	{
		delete prototile.second;
	}
	m_tiles.clear();
}

void TiledLevel::Draw()
{
	if (!m_renderTiles && !m_hasNavigation) return; // If not one flag, bye-bye.
	for (const auto tile : m_level)
	{
		if (m_renderTiles)
		{
			tile->Draw();
		}
		if (m_hasNavigation)
		{
			tile->DrawNavigation();
		}
	}
}

void TiledLevel::Update()
{

}

void TiledLevel::Clean()
{
	// Empty for now. Uses destructor.
}

void TiledLevel::SetLabelsEnabled(bool state)
{
	if (!m_hasNavigation) return;
	for (const auto tile : m_level)
	{
		tile->SetLabelsEnabled(state);
	}
}


void TiledLevel::LinkTiles()
{
	for (int row = 0; row < m_rows; ++row)
	{
		for (int col = 0; col < m_cols; ++col)
		{
			Tile* tile = GetTile(col, row);

			// TopMost Row?
			if (row == 0)
			{
				tile->SetTileNeighbour(TileNeighbour::TOP_TILE, nullptr);
			}
			else
			{
				// setup Top Neighbour
				tile->SetTileNeighbour(TileNeighbour::TOP_TILE, GetTile(col, row - 1));
			}

			// RightMost Col?
			if (col == m_cols - 1)
			{
				tile->SetTileNeighbour(TileNeighbour::RIGHT_TILE, nullptr);
			}
			else
			{
				// setup Right Neighbour
				tile->SetTileNeighbour(TileNeighbour::RIGHT_TILE, GetTile(col + 1, row));
			}

			// BottomMost Row?
			if (row == m_rows - 1)
			{
				tile->SetTileNeighbour(TileNeighbour::BOTTOM_TILE, nullptr);
			}
			else
			{
				// Setup the Bottom Neighbour
				tile->SetTileNeighbour(TileNeighbour::BOTTOM_TILE, GetTile(col, row + 1));
			}

			// LeftMost Col?
			if (col == 0)
			{
				tile->SetTileNeighbour(TileNeighbour::LEFT_TILE, nullptr);
			}
			else
			{
				// Setup the Left Neighbour
				tile->SetTileNeighbour(TileNeighbour::LEFT_TILE, GetTile(col - 1, row));
			}
		}
	}
}

Tile* TiledLevel::GetTile(unsigned col, unsigned row) const
{
	return m_level[row * m_cols + col];
}

std::vector<Tile*>& TiledLevel::GetLevel()
{
	return m_level;
}

std::vector<Tile*>& TiledLevel::GetImpassables()
{
	return m_impassables;
}

std::vector<Tile*>& TiledLevel::GetHazards()
{
	return m_hazards;
}
