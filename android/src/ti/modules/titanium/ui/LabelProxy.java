package ti.modules.titanium.ui;

import org.appcelerator.titanium.TiContext;
import org.appcelerator.titanium.view.TiUIView;
import org.appcelerator.titanium.view.TiViewProxy;

import ti.modules.titanium.ui.widget.TiUILabel;

public class LabelProxy extends TiViewProxy
{
	public LabelProxy(TiContext tiContext, Object[] args)
	{
		super(tiContext, args);
	}

	@Override
	public TiUIView createView()
	{
		return new TiUILabel(this);
	}
}