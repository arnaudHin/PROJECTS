package fr.eseo.poo.projet.artiste.vue.ihm;

import java.awt.Color;
import java.awt.GridLayout;
import java.text.ParseException;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JToggleButton;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import fr.eseo.poo.projet.artiste.controleur.actions.ActionChoisirCouleur;
import fr.eseo.poo.projet.artiste.controleur.actions.ActionChoisirForme;
import fr.eseo.poo.projet.artiste.controleur.actions.ActionChoisirRemplissage;
import fr.eseo.poo.projet.artiste.controleur.actions.ActionEffacer;
import fr.eseo.poo.projet.artiste.controleur.actions.ActionSelectionner;
import fr.eseo.poo.projet.artiste.modele.formes.Etoile;

public class PanneauBarreOutils extends JPanel {

	private static final long serialVersionUID = 1L;
	public static final String BRANCHE_SPINNER_NOM ="Nombre Branche" ;
	public static final String LONGUEUR_SPINNER_NOM ="Longueur Branche" ;
	private PanneauDessin panneauDessin;
	public JSpinner spinnerNombreBranche;
	public JSpinner spinnerLongueurBranche;
	private ButtonGroup boutons = new ButtonGroup();

	
	public PanneauBarreOutils(PanneauDessin panneauDessin) {
		super();
		this.panneauDessin = panneauDessin;
		initComponents();
		initComposants2();
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS)); 
	}
	
	
	public void initComponents() {
		JButton btnEff = new JButton(new ActionEffacer(this.panneauDessin)); 
		btnEff.setName(ActionEffacer.NOM_ACTION);
		btnEff.setText(ActionEffacer.NOM_ACTION);
		btnEff.setBackground(Color.red);
		
		JButton btnColor = new JButton(new ActionChoisirCouleur(this.panneauDessin));
		btnColor.setName(ActionChoisirCouleur.NOM_ACTION);
		btnColor.setText(ActionChoisirCouleur.NOM_ACTION);
		btnColor.setBackground(Color.orange);
		
		JToggleButton btnSelect = new JToggleButton(new ActionSelectionner(this.panneauDessin));
		btnSelect.setName(ActionSelectionner.NOM_ACTION);
		btnSelect.setText(ActionSelectionner.NOM_ACTION);
		btnSelect.setBackground(Color.orange);
		
		JCheckBox checkBoxRemplie = new JCheckBox(new ActionChoisirRemplissage(this.panneauDessin));
		checkBoxRemplie.setName(ActionChoisirRemplissage.NOM_ACTION);
		checkBoxRemplie.setText(ActionChoisirRemplissage.NOM_ACTION);
		
		JToggleButton btnOutilLigne = new JToggleButton(new ActionChoisirForme(this.panneauDessin, 
				this, ActionChoisirForme.NOM_ACTION_LIGNE));
		btnOutilLigne.setName(ActionChoisirForme.NOM_ACTION_LIGNE);
		btnOutilLigne.setText(ActionChoisirForme.NOM_ACTION_LIGNE);
		JToggleButton btnOutilEllipse = new JToggleButton(new ActionChoisirForme(this.panneauDessin, 
				this, ActionChoisirForme.NOM_ACTION_ELLIPSE));
		btnOutilEllipse.setName(ActionChoisirForme.NOM_ACTION_ELLIPSE);
		btnOutilEllipse.setText(ActionChoisirForme.NOM_ACTION_ELLIPSE);
		JToggleButton btnOutilCercle = new JToggleButton(new ActionChoisirForme(this.panneauDessin, 
				this, ActionChoisirForme.NOM_ACTION_CERCLE));
		btnOutilCercle.setName(ActionChoisirForme.NOM_ACTION_CERCLE);
		btnOutilCercle.setText(ActionChoisirForme.NOM_ACTION_CERCLE);

		this.boutons.add(btnOutilLigne);
		this.boutons.add(btnOutilEllipse);
		this.boutons.add(btnOutilCercle);
		this.boutons.add(btnSelect);
		
		JPanel contentBtnActions = new JPanel();
		contentBtnActions.setLayout(new GridLayout(4, 1));
		contentBtnActions.add(btnEff);
		contentBtnActions.add(btnColor);
		contentBtnActions.add(btnSelect);
		contentBtnActions.add(checkBoxRemplie);
		this.add(contentBtnActions);
		
		JPanel contentBtnFormes = new JPanel(new GridLayout(3, 1));
		contentBtnFormes.add(btnOutilLigne);
		contentBtnFormes.add(btnOutilCercle);
		contentBtnFormes.add(btnOutilEllipse);
		this.add(contentBtnFormes);
	}
	
	public void initComposants2() {
		
		JToggleButton btnOutilEtoile = new JToggleButton(new ActionChoisirForme(this.panneauDessin, 
				this, ActionChoisirForme.NOM_ACTION_ETOILE));
		btnOutilEtoile.setName(ActionChoisirForme.NOM_ACTION_ETOILE);
		btnOutilEtoile.setText(ActionChoisirForme.NOM_ACTION_ETOILE);	
		
		JLabel labelNombreBranche = new JLabel(PanneauBarreOutils.BRANCHE_SPINNER_NOM);
		SpinnerNumberModel rotNombreBranche = new SpinnerNumberModel(Etoile.NOMBRE_BRANCHES_PAR_DEFAUT, 3, 15, 1);
		this.spinnerNombreBranche = new JSpinner(rotNombreBranche);
		this.spinnerNombreBranche.setName(PanneauBarreOutils.BRANCHE_SPINNER_NOM);
		spinnerNombreBranche.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(e.getSource() == spinnerNombreBranche) {
					try { spinnerNombreBranche.commitEdit();} catch (ParseException pe) {	}	}	} });
		JLabel labelLongueurBranche = new JLabel(PanneauBarreOutils.LONGUEUR_SPINNER_NOM);
		SpinnerNumberModel rotLonguerBranche = new SpinnerNumberModel(Etoile.LONGUEUR_BRANCHE_PAR_DEFAUT, 0, 1, 0.01);
		this.spinnerLongueurBranche = new JSpinner(rotLonguerBranche);
		this.spinnerLongueurBranche.setName(PanneauBarreOutils.LONGUEUR_SPINNER_NOM);
		spinnerLongueurBranche.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				if(e.getSource() == spinnerLongueurBranche) {
					try { spinnerLongueurBranche.commitEdit(); } catch (ParseException pe2) {	} } } });		
		
		this.boutons.add(btnOutilEtoile);	
		
		JPanel contentEllipse = new JPanel(new GridLayout(5, 1));
		contentEllipse.add(btnOutilEtoile);
		contentEllipse.add(labelNombreBranche);
		contentEllipse.add(spinnerNombreBranche);
		contentEllipse.add(labelLongueurBranche);
		contentEllipse.add(spinnerLongueurBranche);
		this.add(contentEllipse);			
	}
	
	public int getNbBranches() {
		return (int)spinnerNombreBranche.getValue();
	}
	public double getLongueurBranche() {
		return (double) spinnerLongueurBranche.getValue();
	}
	

}
