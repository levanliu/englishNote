## GEF

### what is GEF?

```
Graphical Editing Framework
```

### What is architecture of GEF?

```
MVC
```

### what is main components of GEF?

```
Model: (EMF)
View: (Graphical Viewer)
Controller: (EditPart)
```

### How does GEF work?

1. Create a model: Define the data structure that represents the elements to be edited in the graphical editor. In SmarTEST8, it's EMF.
2. Create an EditPart: EditPart is a interface, it will handle the interaction between the model and view. Implement the org.eclipse.gef.EditPart interface to create a controller for the model element.
3. Create an EditPartFactory: Implement the org.eclipse.gef.EditPartFactory interface to create EditParts for different model elements. The EditPartFactory is responsible for creating the appropriate EditPart for each model element.
4. Create a GraphicalViewer: create a org.eclipse.gef.GraphicalViewer to display the graphcial representation of the model. This viewer will be reponsible for managing the EditParts and their visual representation.
5. Create a RootEditPart: Create a org.eclipse.gef.RootEditPart that acts as the root controller for the graphical editor. This Editpart will manage the creation and deletion of child EditParts.
6. Connect the EditParts: Use the org.eclipse.gef.EditPart hierarchy to connect the EditParts together. Each EditPart should have a reference to its parent EditPart and its child EditParts.
7. Implement EditPart behavior: Implement the necessary methods in the EidtPart to handle user interactions, such as selection, dragging, and resizing. These methods will update the model and the view accordingly.
8. Register the EditPart: Register the EditPart and the EditPartFactory with the GraphicalViewer. This will allow the viewer to create and manage the EditParts.

