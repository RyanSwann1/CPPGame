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
TileLayer::TileLayer(const std::vector<std::vector<int>>& tileLayer, const std::string& tileSheetName)
	: m_name(tileSheetName),
	m_tileLayer(tileLayer)
{}

const std::vector<std::vector<int>>& TileLayer::getTileLayer() const
{
	return m_tileLayer;
}

const std::string & TileLayer::getName() const
{
	return m_name;
}

void TileLayer::draw(const TileSheet& tileSheet, sf::RenderWindow& window, sf::Vector2i levelSize) const
{
	for (int y = 0; y < levelSize.y; ++y)
	{
		for (int x = 0; x < levelSize.x; ++x)
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
Level::Level(sf::Vector2i levelSize, std::vector<TileLayer> tileLayers, std::unordered_map<std::string, TileSheet> tileSheets,
	std::vector<sf::FloatRect>&& collisionLayer, std::vector<sf::Vector2f> entityStartingPositions)
	: m_levelSize(levelSize),
	m_tileLayers(tileLayers),
	m_tileSheets(tileSheets),
	m_collisionLayer(std::move(collisionLayer))
{
	for (sf::Vector2f entityStartingPosition : entityStartingPositions)
	{
		m_entities.emplace_back(m_tileSheets.begin()->second, entityStartingPosition);
	}
}

sf::Vector2i Level::getSize() const
{
	return m_levelSize;
}

const TileLayer & Level::getTileLayer() const
{
	return m_tileLayers.front();
}

const std::vector<sf::FloatRect>& Level::getCollisionLayer() const
{
	assert(!m_collisionLayer.empty());
	return m_collisionLayer;
}

const TileSheet & Level::getTileSheet(const std::string & name) const
{
	auto iter = m_tileSheets.find(name);
	assert(iter != m_tileSheets.cend());
	return iter->second;
}

void Level::update()
{
	for (auto& entity : m_entities)
	{
		entity.update();
	}
}

void Level::draw(sf::RenderWindow& window) const
{
	for (const auto& tileLayer : m_tileLayers)
	{
		tileLayer.draw(m_tileSheets.begin()->second, window, m_levelSize);
	}

	for (const auto& entity : m_entities)
	{
		entity.draw(window);
	}
}