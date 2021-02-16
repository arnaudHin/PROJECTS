package fr.eseo.poo.projet.artiste.modele.formes;

import java.awt.Point;


import java.awt.Polygon;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.Remplissable;

public class Etoile extends Forme implements Remplissable {

	public final static int NOMBRE_BRANCHES_PAR_DEFAUT = 3 + (int) Math.floor( Math.random()*(15 - 3) );
	public final static double ANGLE_PREMIERE_BRANCHE_PAR_DEFAUT = (Math.floor(Math.random()) * (2*Forme.PI)) - Forme.PI;
	public final static double LONGUEUR_BRANCHE_PAR_DEFAUT = 0.1 + (Math.random() * 1 - 0.1);
	
	private List<Coordonnees> coordonnees;
	private int nombreBranches;
	private double anglePremiereBranche;
	private double longueurBranche;
	private boolean remplie;
	
	public Etoile(Coordonnees coordonnees, double taille, int nombreBranches, double anglePremiereBranche, double longueurBranche) {
		super(coordonnees, taille, taille);
		this.coordonnees = new ArrayList<Coordonnees>();
		this.setRempli(false);
		this.setLargeur(taille);
		this.setHauteur(taille);
		this.setNombreBranches(nombreBranches);
		this.setLongueurBranche(longueurBranche);
		this.setAnglePremiereBranche(anglePremiereBranche);
		this.coordonnees = new ArrayList<Coordonnees>();
		this.setSommets();
	}
	
	public Etoile(Coordonnees coordonnees, double taille) {
		this(coordonnees, taille, NOMBRE_BRANCHES_PAR_DEFAUT, ANGLE_PREMIERE_BRANCHE_PAR_DEFAUT, LONGUEUR_BRANCHE_PAR_DEFAUT);
	}
	public Etoile(Coordonnees coordonnees) { 
		this(coordonnees, Forme.LARGEUR_PAR_DEFAUT); 
		}
	
	public Etoile(double taille) { 
		this(new Coordonnees(), taille); 
		}
	
	
	public Etoile() { 
		this(new Coordonnees()); 
		}

	public void setPosition(Coordonnees position) { 
		super.setPosition(position); 
		}
	
	public void setLargeur(double largeur){
		if (largeur < 0) { 
			throw new IllegalArgumentException(); 
		}
		super.setLargeur(largeur); 
		if(this.getHauteur() != this.getLargeur()) { 
			this.setHauteur(largeur); 
			}
		if(this.getNombreBranches() != 0 && this.getLongueurBranche() != 0) { 
			this.setSommets(); 
		}
	}
	
	
	public void setHauteur(double hauteur){
		if (hauteur < 0) { 
			throw new IllegalArgumentException(); 
			}
		super.setHauteur(hauteur);
		if(this.getHauteur() != this.getLargeur()) { 
			this.setLargeur(hauteur); 
		}		
	}
	
	
	public void setNombreBranches(int nbBranches) { 
		if (nbBranches < 3 || nbBranches > 15) { 
			throw new IllegalArgumentException(); 
		}		
		this.nombreBranches = nbBranches;
		this.setSommets(); 
			
	}
	public void setLongueurBranche(double longueur) { 
		if (longueur < 0 || longueur > 1.0) { 
			throw new IllegalArgumentException(); 
			}		
		this.longueurBranche = longueur; 
		this.setSommets(); 
				
	}
	
	public void setAnglePremiereBranche(double angle) {
		if (angle < -Forme.PI || angle > Forme.PI) {
			throw new IllegalArgumentException(); 
			}			
		this.anglePremiereBranche = angle; 
		}
	
	public List<Coordonnees> getCoordonnees(){ 
		return this.coordonnees; 
		}
	public int getNombreBranches() { 
		return this.nombreBranches; 
		}
	public double getLongueurBranche() { 
		return this.longueurBranche; 
		}
	public double getAnglePremiereBranche() { 
		return this.anglePremiereBranche; 
		}
	
	public void setSommets() {
		double rayon = this.getLargeur()/2;
		Coordonnees centre = new Coordonnees(this.getPosition().getAbscisse() +rayon, this.getPosition().getOrdonnee()+rayon);
		double angleEntreSommet = Forme.PI/this.getNombreBranches();
		double angleActuel = this.getAnglePremiereBranche();
		this.getCoordonnees().clear();	
		for (int i=0 ; i<this.getNombreBranches()*2 ; i++) {
			if(i==0) {
				double abs0 = centre.getAbscisse() + rayon*Math.cos(angleActuel);
				double ord0 = centre.getOrdonnee() + rayon*Math.sin(angleActuel);
				Coordonnees sommet0 = new Coordonnees(abs0, ord0);
				this.getCoordonnees().add(sommet0);
				angleActuel += angleEntreSommet;	
			}
			else if(i%2 == 0) {
				double abscisse = centre.getAbscisse() + rayon*Math.cos(angleActuel);
				double ordonnee = centre.getOrdonnee() + rayon*Math.sin(angleActuel);
				Coordonnees sommetGrand = new Coordonnees(abscisse, ordonnee);
				this.getCoordonnees().add(sommetGrand);
				angleActuel += angleEntreSommet;
			}
			else{
				double abscisse = centre.getAbscisse() + (1 - this.getLongueurBranche())*rayon*Math.cos(angleActuel);
				double ordonnee = centre.getOrdonnee() + (1 - this.getLongueurBranche())*rayon*Math.sin(angleActuel);
				Coordonnees sommetCreux = new Coordonnees(abscisse, ordonnee);
				this.getCoordonnees().add(sommetCreux);
				angleActuel += angleEntreSommet;
			}
		}
	}
	
	
	public String toString() {
		Locale currentLocale = Locale.getDefault();
		NumberFormat numberFormat = NumberFormat.getNumberInstance(currentLocale);
		numberFormat.setMaximumFractionDigits(2);
		numberFormat.setMinimumFractionDigits(1);
		numberFormat.setGroupingUsed(false);
		String couleur = "";
		if(currentLocale.getLanguage().equals("fr")) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",V"+String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());
		}
		else if(currentLocale.getLanguage().equals("en")) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",G"+String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());		
		}			
		if(this.remplie) {
			return "["+this.getClass().getSimpleName() +"-Rempli] : " +"pos ("+numberFormat.format(this.getPosition().getAbscisse())+
					" , "+numberFormat.format(this.getPosition().getOrdonnee())+
					") dim "+numberFormat.format(this.getLargeur())+" x "+numberFormat.format(this.getHauteur())+ " périmètre : "+
					numberFormat.format(this.perimetre())+" aire : "+numberFormat.format(this.aire())+
					" couleur = "+ couleur;
		}
		
		return "["+this.getClass().getSimpleName() +"] : " +"pos ("+numberFormat.format(this.getPosition().getAbscisse())+" , "+
		numberFormat.format(this.getPosition().getOrdonnee())+
				") dim "+numberFormat.format(this.getLargeur())+" x "+numberFormat.format(this.getHauteur())+ " périmètre : "+
				numberFormat.format(this.perimetre())+" aire : "+numberFormat.format(this.aire())+
				" couleur = "+ couleur;
	}
	
	public double aire() {
		double rayon = this.getLargeur()/2;
		double base = this.getCoordonnees().get(0).distanceVers(this.getCoordonnees().get(2));
		double hauteurPetite = rayon*Math.cos(Forme.PI/this.getNombreBranches()) - (1 - this.getLongueurBranche())*rayon;
		double airePetitTriangle = base*hauteurPetite/2;
		
		double aireGrandTriangle = base*rayon*Math.cos(Forme.PI/this.getNombreBranches())/2;
		
		return (aireGrandTriangle*this.getNombreBranches()) - airePetitTriangle*this.getNombreBranches();
	}

	public double perimetre() {
		return 2*this.getNombreBranches() * this.getCoordonnees().get(0).distanceVers(this.getCoordonnees().get(1));
	}

	public boolean contient(Coordonnees coord) {

		int[] pointsX = new int[this.getCoordonnees().size()];
		int[] pointsY = new int[this.getCoordonnees().size()];
		for(int i =0;i<this.getCoordonnees().size();i++) {
			pointsX[i] = (int)this.getCoordonnees().get(i).getAbscisse();
			pointsY[i] = (int)this.getCoordonnees().get(i).getOrdonnee();
		}
		Polygon figure = new Polygon(pointsX, pointsY, this.getCoordonnees().size());
		
		Point point = new Point((int) coord.getAbscisse(),(int) coord.getOrdonnee());
		
		return figure.contains(point);
	}

	public void setRempli(boolean modeRempli) { 
		this.remplie = modeRempli; 
		}
	public boolean estRempli() {
		return this.remplie; 
		}
}
