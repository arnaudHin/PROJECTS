package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.JOptionPane;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionEffacer extends AbstractAction {
	
	private static final long serialVersionUID = 1L;
	public static final String NOM_ACTION = "Effacer Tout"; 
	private PanneauDessin panneauDessin;
	
	public ActionEffacer(PanneauDessin panneauDessin) { 
		super(ActionEffacer.NOM_ACTION); 
		this.panneauDessin = panneauDessin; 
		}	
	
	public void actionPerformed(ActionEvent arg0) {
	
		if(JOptionPane.showConfirmDialog( this.panneauDessin,"Attention tout sera supprimé", 
				ActionEffacer.NOM_ACTION, JOptionPane.YES_NO_OPTION) == 0) { 
			this.panneauDessin.getVueFormes().clear(); 
			this.panneauDessin.repaint(); 
			}
		else {
			
		}
	}
}


