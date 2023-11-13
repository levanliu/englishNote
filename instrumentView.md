### Instrument View

| Responsibility  | Location   | Module Documentation |
|-------------- | -------------- | -------------- |
| awg, clock, dcVI, digInOut, digitizer, loopback, rfMeas, rfStim, rfVna, utility    |     | isv.ui.overview.md  |


In general Instrument view is implemented based on Eclipse view.
Instrument view is splitted into 4 modules for better modularity and maintainability: InstrumentUI, InstrumentCore, DiagramUI and DiagramCore. InstrumentUI is responsible for the UI part of Instrument view, InstrumentCore is responsible for the core part of Instrument view, DiagramUI is responsible for diagram rendering, DiagramCore is responsible for diagram data model.


EditPart is a key component in Eclipse Plugin development that is used in the Graphical Editing Framew
ork (GEF). It acts as a controller between the model and the view in a graphical editor. EditPart is respons
ible for managing the creation, deletion, and updating of the visual representation of a model element.

The usage of EditPart in Eclipse Plugin development involves the following steps:

1. Create a model: Define the data structure that represents the elements to be edited in the graphical edit
or. This model should implement the necessary interfaces, such as `org.eclipse.gef.EditPart`.

2. Create an EditPart: Implement the `org.eclipse.gef.EditPart` interface to create a controller for the mod
el element. This EditPart will handle the interaction between the model and the view.

3. Create a EditPartFactory: Implement the `org.eclipse.gef.EditPartFactory` interface to create EditParts f
or different model elements. The EditPartFactory is responsible for creating the appropriate EditPart for ea
ch model element.

4. Create a GraphicalViewer: Create a `org.eclipse.gef.GraphicalViewer` to display the graphical representat
ion of the model. This viewer will be responsible for managing the EditParts and their visual representation
.

5. Create a RootEditPart: Create a `org.eclipse.gef.RootEditPart` that acts as the root controller for the g
raphical editor. This EditPart will manage the creation and deletion of child EditParts.

6. Connect the EditParts: Use the `org.eclipse.gef.EditPart` hierarchy to connect the EditParts together. Ea
ch EditPart should have a reference to its parent EditPart and its child EditParts.

7. Implement EditPart behavior: Implement the necessary methods in the EditPart to handle user interactions,
 such as selection, dragging, and resizing. These methods will update the model and the view accordingly.

8. Register the EditPart: Register the EditPart and the EditPartFactory with the GraphicalViewer. This will 
allow the viewer to create and manage the EditParts.



```yaml

Select instrument
notify event
show with context
parse context to get signal
signal changed(new job)

get instrument states [DebugSupport]
create diagram model
fill instrument states to model

notify UI refresh
refresh UI

get diagram model
set diagram model

draw diagram

```

```yaml
click buttion
buttion click event is triggered
get diagram action by action ID
schedule new job to execute action

execute action
build escape meas setup

read values from diagram model

execute escape meas(DebugSupport)
get result
parse result

set result to diagram model

schedule job to update instrument (Update instrument states and
fire event to refresh UI)

notify UI refresh

refresh UI

get diagram model (After update instrument job is done. UI job
scheduled to refresh UI)

set diagram model
draw diagram
```
