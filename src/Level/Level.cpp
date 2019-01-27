#include "Level.h"
#include <utility>
#include <assert.h>

//TileSheet
TileSheet::TileSheet(const std::string& name, int tileSize, int columns)
	: m_texture(),
	m_tileSize(tileSize),
	m_columns(columns)
{
	m_texture.loadFromFile(name);
}

sf::IntRect TileSheet::getTileLocation(int tileID) const
{
	return sf::IntRect((tileID % m_columns) * m_tileSize,
		(tileID / m_columns) * m_tileSize, m_tileSize, m_tileSize);
}

//TileLayer
TileLayer::TileLayer(const std::vector<std::vector<int>>& tileLayer, const std::string& tileSheetName, sf::Vector2i mapSize)
	: m_name(tileSheetName),
	m_tileLayer(tileLayer),
	m_mapSize(mapSize)
{}

const std::string & TileLayer::getName() const
{
	return m_name;
}

void TileLayer::draw(const TileSheet& tileSheet, sf::RenderWindow& window) const
{
	for (int y = 0; y < m_mapSize.y; ++y)
	{
		for (int x = 0; x < m_mapSize.x; ++x)
		{
			const int tileID = m_tileLayer[y][x];
			if (tileID >= 0)
			{
				sf::Sprite tile(tileSheet.m_texture, tileSheet.getTileLocation(tileID));
				tile.setPosition(sf::Vector2f(x * tileSheet.m_tileSize, y * tileSheet.m_tileSize));
				window.draw(tile);
			}
		}
	}
}

//Level
Level::Level(const std::vector<TileLayer>& tileLayers, const std::unordered_map<std::string, TileSheet>& tileSheets)
	: m_tileLayers(tileLayers),
	m_tileSheets(tileSheets)
{}

void Level::draw(sf::RenderWindow& window) const
{
	for (const auto& tileLayer : m_tileLayers)
	{
		auto iter = m_tileSheets.find(tileLayer.getName());
		assert(iter != m_tileSheets.cend());
		tileLayer.draw(iter->second, window);
	}
}