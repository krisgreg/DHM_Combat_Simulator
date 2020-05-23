#include "SceneObjectPlaceableInEditor.h"



lbe::SceneObjectPlaceableInEditor::SceneObjectPlaceableInEditor(sf::Vector2f Pos) : SceneObject(Pos)
{
	bIsPlaceableInEditor = true;
}


lbe::SceneObjectPlaceableInEditor::~SceneObjectPlaceableInEditor()
{
}
